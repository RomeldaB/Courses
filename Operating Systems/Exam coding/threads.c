/*
* pthread/pthread-echo.c --
*/

//#define _REENTRANT
#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

static void*
work(void *data)
{
    char *msg = (char *) data;
    printf("%s ", msg);
    return NULL;
}

int
main(int argc, char *argv[])
{
    int i, r;
    pthread_t tids[argc];
    
    for (i = 1; i < argc; i++) {
        r = pthread_create(&tids[i], NULL, work, argv[i]); /// r=0 if thread is created
        if(r) {
            fprintf(stderr, "failed to create thread: %s\n", strerror(r));
        }
    }

    for (i = 1; i < argc; i++) {
        if (tids[i]) {
            (void) pthread_join(tids[i], NULL);
        }
    }
    printf("\n");
    return EXIT_SUCCESS;
}

// ./t 1 2 3 4 5 6 7 8 9 10 gives 3 2 1 4 5 7 6 8 9 10 