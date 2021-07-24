#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#define N 5
static long int a[N];
typedef struct {
pthread_t thread;
int tid;
long int value;
} thread_state_t;
static void* weird(void *arg)
{
thread_state_t *ts = (thread_state_t *) arg;
int me = ts->tid;
int ne = (me > 0) ? me - 1 : N - 1;
while (1) {
if (a[ne] == -1) {
a[me] = a[ne];
break;
} else if (a[ne] == ts->value) {
a[me] = -1;
printf("\n%d: The lucky number is: %ld\n", me, a[ne]);
break;
} else if (a[ne] > a[me]) {
a[me] = a[ne];
} else {
/* do nothing */
}
}
return NULL;
}
int main(int argc, char **argv)
{
int i;
thread_state_t ts[N];
srandom(getpid()); /* initialize the random number generator */
for (i = 0; i < N; i++) {
ts[i].value = a[i] = random(); /* a random non-negative number */
ts[i].tid = i; /* an id in the range [0..N-1] */
printf("%d: %12ld\n", ts[i].tid, ts[i].value);
}
for (i = 0; i < N; i++) pthread_create(&ts[i].thread, NULL, weird, &ts[i]);
for (i = 0; i < N; i++) pthread_join(ts[i].thread, NULL);
return EXIT_SUCCESS;
}