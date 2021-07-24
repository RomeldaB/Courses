#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include "coins.h"

  ///////////////////////
 ///////* MAIN *////////
///////////////////////
int people = 100;
int flips = 10000;
char coins[21] = "OOOOOOOOOOXXXXXXXXXX";
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER, 
						arr_m[20] = {
							PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
							PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
							PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, 
							PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
							PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, 
							PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
							PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, 
							PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
							PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, 
							PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER
						};


int main(int argc, char* argv[])
{
    int opt;
    double t1, t2, t3;
    char *endptr;

    while((opt = getopt(argc, argv, "n:p:")) != -1)
    {
        switch (opt)
        {
        	case 'n':
	            if( (flips = atoi(optarg)) == 0 || flips < 0) {
	                fprintf(stderr, "Error,argument of -n must be a positive and non zero number!!\n");
	                exit(EXIT_FAILURE); // Failure
	            }
	            break;
	        case 'p':
	            if( (people = atoi(optarg)) == 0 || people < 0) {
	                fprintf(stderr, "Error,argument of -p must be a positive and non zero number!!\n");
	                exit(EXIT_FAILURE); // Failure
	            }            
	            break;
	        default:
	            fprintf(stderr, "Unknown option!\n");
	            exit(EXIT_FAILURE);
	            break;
        }
    }

    // First strategy
    printf("coins: %s (start - global lock)\n", coins);
    t1 = timeit(people, global_lock);
    printf("coins: %s (end - global lock)\n", coins);
    printf("%d threads x %d flips: %lf ms\n\n", people, flips, t1);

    // Second strategy
    printf("coins: %s (start - iteration lock)\n", coins);
    t2 = timeit(people, iteration_lock);
    printf("coins: %s (end - iteration lock)\n", coins);
    printf("%d threads x %d flips: %lf ms\n\n", people, flips, t2);

    // Third strategy
    printf("coins: %s (start - coin lock)\n", coins);
    t3 = timeit(people, coin_lock);
    printf("coins: %s (end - coin lock)\n", coins);
    printf("%d threads x %d flips: %lf ms\n\n", people, flips, t3);

    return 0;
}

