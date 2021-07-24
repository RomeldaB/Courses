/*
* race/race.c --
*
A simple program demonstrating race conditions. Note that it
is system specific how frequently race conditions occur. Run
this program using watch -n 0.5 -d "./race | xargs -n 1 | sort -n | xargs"
and lean back and you may see numbers suddenly changing.
*/
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static unsigned int c = 0;
/* shared variable */
static void *
count(void *ignored)
{
    int i;
    const struct timespec ts = { .tv_sec = 0, .tv_nsec = 123456 };
    for (i = 0; i < 10; i++) {
        nanosleep(&ts, NULL);
        c++;
        printf(" %d", c);
    }
    return NULL;
}

int
main(int argc, char *argv[])
{
    const unsigned int num = 8;
    int i, rt[num];
    pthread_t t[num];
    for (i = 0; i < num; i++) {
        rt[i] = pthread_create(&t[i], NULL, count, NULL);
        if (rt[i]) {
            fprintf(stderr, "thread creation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    for (i = 0; i < num; i++) {
        (void) pthread_join(t[i], NULL);
    }
    printf("\n");
    return EXIT_SUCCESS;
}

// Result:  1 3 6 4 2 7 5 8 9 10 11 12 13 14 15 16 17 18 19 
// 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 
// 39 40 41 42 43 44 45 46 47 48 49 51 50 52 53 54 55 56 57 
// 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80