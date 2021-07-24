/*
A simple program to fork and wait processes.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

static void
work(const char *msg)
{
    printf("%s ", msg);
    exit(EXIT_SUCCESS); // exits current processes
    /*
        When removing exit, it will print the "path" for each process,
        so, for ./p 1 2 it prints once 1, once 2, and once 1 2 separated by \n.
    */
}

int
main(int argc, char *argv[])
{
    int i, status;
    pid_t pids[argc];
    for (i = 1; i < argc; i++) {
        pids[i] = fork(); // for each iteration, only 1 child process is formed
        if (pids[i] == -1) {
            fprintf(stderr, "failed to fork: %s\n", strerror(errno));
            continue;
        }
        // if child:
        if(pids[i] == 0) {
            work(argv[i]);
        }
    }
    for (i = 1; i < argc; i++) {
        // if parent:
        if (pids[i] > 0) {
            (void) waitpid(pids[i], &status, 0); // waits for child process to end execution
        }
    }
    printf("\n");
    return EXIT_SUCCESS;
}

// for ./a.out a b c -> it prints: a b c