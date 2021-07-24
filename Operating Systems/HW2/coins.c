#include "coins.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

  //////////////////////
 /////* METHODS *//////
//////////////////////

extern char coins[21];
extern int people, flips;
extern pthread_mutex_t mutex, arr_m[20];

 /*Similar function to the one in the slide 68*/
void run_threads(int n, void* (*function)(void*)) {
    int i, r;
    pthread_t tids[n];

    for (i = 0; i < n; i++) {
        r = pthread_create(&tids[i], NULL, function, NULL);
        if (r) {
            fprintf(stderr, "Failed to create thread: %s\n", strerror(r));
            exit(1);
        }
    }

    for (i = 0; i<n; i++) {
        if (tids[i]) {
            (void) pthread_join(tids[i], NULL);
        }
    }
}
// Provided in the pdf
double timeit(int n, void* (*proc)(void *)) {
    clock_t t1, t2;
    t1 = clock();
    run_threads(n, proc);
    t2 = clock();
    return ((double) t2 - (double) t1) / CLOCKS_PER_SEC * 1000;
}

void *global_lock(void *args) {
    int i, j;
    pthread_mutex_lock(&mutex);
    for(i = 0; i < flips; i++) {
        for(j = 0; j < 20; j++) {
            flip_coin(&coins[j]);
        }
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *iteration_lock(void *args) {
    int i,j;
    for(i = 0; i < flips; i++) {
        pthread_mutex_lock(&mutex);

        for(j = 0; j < 20; j++) {
            flip_coin(&coins[j]);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *coin_lock(void *args) {
    for(int i = 0; i < flips; i++) {
        for(int j = 0; j < 20; j++) {
            pthread_mutex_lock(&arr_m[j]);
            flip_coin(&coins[j]);
            pthread_mutex_unlock(&arr_m[j]);
        }
    }
    return NULL;
}

void flip_coin(char* coin) {
    if(*coin =='O'){
        *coin = 'X';
    } else {
        *coin = 'O';
    }
}