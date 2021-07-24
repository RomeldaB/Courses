#ifndef COINS_H
#define COINS_H

  ////////////////////////////
 //////* DECLARATIONS *//////
////////////////////////////

void run_threads(int n, void* (*proc)(void*));
double timeit(int n, void* (*proc)(void *));
void *global_lock(void *args);
void *iteration_lock(void *args);
void *coin_lock(void *args);
void flip_coin(char* coin);

#endif