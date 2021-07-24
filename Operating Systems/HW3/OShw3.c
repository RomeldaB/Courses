//https://www.techiedelight.com/circular-queue-implementation-c/
// Reference for the used queue

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

// The queue I will be using
struct queue
{
	int *items;		// array to store queue elements
	int maxsize;	// maximum capacity of the queue
	int front;		// front points to front element in the queue (if any)
	int rear;		// rear points to last element in the queue
	int size;		// current capacity of the queue
};
// The person struct
struct person {
    int type; // 0->client 1->detective
    int count;
};

// Prototypes of queue functions
struct queue* newQueue(int size);
int  size(struct queue *pt);
int  isEmpty(struct queue *pt);
int  front(struct queue *pt);
void push(struct queue *pt, int x);
void pop(struct queue *pt);

// d c stand for the current nr of dets and cls in the bar
int d = 0, c = 0, d_shift = 0, c_shift = 0; // shift are used with conditional waiting

// Responsible for locking and unlocking
pthread_mutex_t mutex   = PTHREAD_MUTEX_INITIALIZER;
// Responsible for waking all clients when a detective enters
pthread_cond_t  clients = PTHREAD_COND_INITIALIZER;
// responsible of waking a single detective he/she enters before client
pthread_cond_t *detectives;


// Detectives and clients queues
struct queue *qc, *qd;


// Prototypes of the other functions
static void client_visit_bar(struct person* p);
static void detective_visit_bar(struct person* p);
static void run_threads (int total_c, int total_d);
static void *enjoy_life(void *data);

  //////////////////////////
 ////////// MAIN //////////
//////////////////////////

int main(int argc, char* argv[])
{
    int opt, total_c = 1, total_d = 1;
    while( (opt = getopt(argc, argv, "d:c:") ) >= 0) 
    {
        if(opt == 'd') {
            if((total_d = atoi(optarg)) == 0 || total_d < 0) {
                fprintf(stderr, "Error,argument of -d must be a positive and non zero number!!\n");
                exit(EXIT_FAILURE); 
            }  
        }else if(opt == 'c') {
            if((total_c = atoi(optarg)) == 0 || total_c < 0) {
                fprintf(stderr, "Error,argument of -c must be a positive and non zero number!!\n");
                exit(EXIT_FAILURE); 
            }  
        }else {
            fprintf(stderr, "Only -c and -d options supported!!\n");
            exit(EXIT_FAILURE);
        }
    }   
    // initialize queues
    qc = newQueue(total_c);
    qd = newQueue(total_d);

    // Initialize the array of condition variables 
    detectives = (pthread_cond_t* )malloc(total_d * sizeof(pthread_cond_t));
    for(int i = 0; i < d; i++) {
        if(pthread_cond_init(&detectives[i], NULL)) {
            fprintf(stderr, "Conditional variable initialization error!\n");
            exit(EXIT_FAILURE);
        }
    }
    
    run_threads(total_c, total_d);

    return 0;
}


static void client_visit_bar(struct person* p)
{
    // Lock the mutex
    if(pthread_mutex_lock(&mutex)) {
        fprintf(stderr, "Mutex locking error!!\n");
        exit(EXIT_FAILURE);
    }

    // Push the new client into the clients queue
    push(qc, p->count);

    (void) printf("bar: %5d c %5d d    c%d entering\n", c, d, p->count);
    //Update counter;
    c++;

    if(d > 0) // there are some detectives
    {
        int first;
        // First detective
        first = front(qd);
        pop(qd);

        // Signal first detective
        if(pthread_cond_signal(&detectives[first])) {
            fprintf(stderr, "Error on conditional signaling\n");
            exit(EXIT_FAILURE);
        }
        // shifts are used for while loop while waiting
        d_shift = 1;

        (void) printf("bar: %5d c %5d d     c%d picked up by d%d\n", c, d, p->count, first);
        // Pop the client        
        pop(qc);
    }else {
        (void) printf("bar: %5d c %5d d    c%d waiting...\n", c, d, p->count);
        c_shift = 0;
        // Wait until a detective enters
        while (c_shift == 0) {
            if(pthread_cond_wait(&clients, &mutex)) {
                fprintf(stderr, "Conditional waiting error!!\n");
                exit(EXIT_FAILURE);
            }
        }
        
        (void) printf("bar: %5d c %5d d    ...c%d waking up\n", c, d, p->count);        
    }
    c--;

    (void) printf("bar: %5d c %5d d    c%d leaving\n", c, d, p->count);
    // Unlock the mutex
    if(pthread_mutex_unlock(&mutex)) {
        fprintf(stderr, "Mutex unlocking error\n");
        exit(EXIT_FAILURE);
    }
}

static void detective_visit_bar(struct person* p)
{
    // Lock the mutex
    if(pthread_mutex_lock(&mutex)) {
        fprintf(stderr, "Mutex locking error!!\n");
        exit(EXIT_FAILURE);
    }

    // Update detective queue
    push(qd, p->count);

    (void) printf("bar: %5d c %5d d    d%d entering\n", c, d, p->count);
    d++;

    if(c > 0 && !isEmpty(qc)) {
        // Signal all clients that a detective came
        if(pthread_cond_broadcast(&clients)) {
            fprintf(stderr, "Error while broadcasting\n");
            exit(EXIT_FAILURE);
        }
        c_shift = 1;

        (void) printf("bar: %5d c %5d d    d%d picking clients", c, d, p->count);

        int h;
        // Empty the clients queue
	    while (!isEmpty(qc)) {
		    h = front(qc);
            pop(qc);
            // print all clients that were picked up by the detective
            (void) printf(" c%d", h);
	    }
        (void) printf("\n");
        // Pop queue as detective leaves
        pop(qd);
    }else {
        (void) printf("bar: %5d c %5d d    d%d waiting...\n", c, d, p->count);
        
        //find detective nr
        int id = p->count;

        d_shift = 0;
        while (d_shift == 0) {
            if(pthread_cond_wait(&detectives[id], &mutex)) {
                fprintf(stderr, "Conditional waiting error!!\n");
                exit(EXIT_FAILURE);
            }
        }
        (void) printf("bar: %5d c %5d d    ...d%d waking up\n", c, d, p->count);        
    }
     
    d--;
    (void) printf("bar: %5d c %5d d    d%d leaving\n", c, d, p->count);

    // Unlocking the mutex
    if(pthread_mutex_unlock(&mutex)) {
        fprintf(stderr, "Mutex unlocking error\n");
        exit(EXIT_FAILURE);
    }
}

static void *enjoy_life(void *data)
{
    srand(time(0));// first we make sure we get diff random nrs
    struct person* p = (struct person*) data;

    // Main loop
    while(1) {
        switch (p->type) {
            case '0': // client
                client_visit_bar(p);
                break;
            case '1': // detective
                detective_visit_bar(p);
                break;    
            default:
                break;
        }

        if(usleep(rand()%100000) == -1) {
            fprintf(stderr, "Error on usleep!!");
            exit(EXIT_FAILURE);
        }
    }
    return NULL;
}

// Run threads function similar to the one the professor used in producer consumer problem
static void run_threads (int total_c, int total_d) 
{
    int total = total_c + total_d;
    pthread_t thread[total];
    struct person ps[total];   

    // Create clients
    for (int i = 0; i<total_c; i++) {
        ps[i].type = '0'; // clients
        ps[i].count = i;
    }
    // Create detectives
    for (int i = 0; i<total_d; i++) {
        ps[i + total_c].type = '1';
        ps[i + total_c].count = i;
    }
    // Create all the threads
    for(int i = 0; i<total; i++) {
        if(pthread_create(&thread[i], NULL, enjoy_life, &ps[i])) {
            fprintf(stderr, "Error on thread creation!\n");
            exit(EXIT_FAILURE); 
        }
    }
    // Join them
    for (int i = 0; i<total; i++) {
        if(thread[i]) {
            if(pthread_join(thread[i], NULL)) {
                fprintf(stderr, "Error on thread join!\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}


/* Here is the implementation of a the circular queue used in the code
   Utility function to initialize queue */
struct queue* newQueue(int size)
{
	struct queue *q = NULL;
	q = (struct queue*)malloc(sizeof(struct queue));
	if(!q) {
        fprintf(stderr, "Memory allocation Error!!");
        exit(EXIT_FAILURE);
    }

	q->items = (int*)malloc(size * sizeof(int));
	q->maxsize = size;
	q->front = 0, q->rear = -1;
	q->size = 0;

	return q;
}

// Utility function to return the size of the queue
int size(struct queue *pt)
{
	return pt->size;
}

// Utility function to check if the queue is empty or not
int isEmpty(struct queue *pt)
{
	return !size(pt);
}

// Utility function to return front element in queue
int front(struct queue *pt)
{
	if (isEmpty(pt)) {
		printf("UnderFlow\nProgram Terminated\n");
		exit(EXIT_FAILURE);
	}

	return pt->items[pt->front];
}

// Utility function to add an element x in the queue
void push(struct queue *pt, int x)
{
	if (size(pt) == pt->maxsize) {
		printf("OverFlow\nProgram Terminated\n");
		exit(EXIT_FAILURE);
	}

	pt->rear = (pt->rear + 1) % pt->maxsize;	// circular queue
	pt->items[pt->rear] = x;
	pt->size++;
}

// Utility function to remove element from the queue
void pop(struct queue *pt)
{
	if (isEmpty(pt)) { // front == rear
		printf("UnderFlow\nProgram Terminated\n");
		exit(EXIT_FAILURE);
	}

	pt->front = (pt->front + 1) % pt->maxsize;	// circular queue
	pt->size--;
}

