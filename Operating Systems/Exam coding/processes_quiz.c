#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

static int x = 0; // no effect (same as without static)

int main(int argc, char *argv[]) {
    pid_t p = getpid();
    x++;
    fork();
    if(!fork()) { // child
        if(fork()) { // do fork() and go to parent
            x++; // increase x only for parent
        }
        x++; // increase x for the recent fork()
    }

    printf("p%d: x = %d\n", getpid() - p, x); // getpid() - p increases by 1 for each new crated child
    return 0;
}

/* Result:
p0: x = 1
p1: x = 1
p2: x = 3
p4: x = 2
p3: x = 3
p5: x = 2
*/