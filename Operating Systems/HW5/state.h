#ifndef _STATE_H
#define _STATE_H
#include <unistd.h>
#include <event2/event.h>

// State of game
typedef struct state {
	char fortune[33];
	char missing[33];
	int correct;
	int guesses_number;
} State;

// Connection node
typedef struct connection {
   State *state;
   int sock; // socket descriptor of the connection
   struct connection *next;
   struct event *ev;
} Connection;

int remove_connection(Connection **head, int c);
Connection* add_connection(Connection **head, int c);
// Found in professor's source code folder
int tcp_listen(const char *host, const char *port);
int tcp_accept(int fd);
int tcp_close(int fd);
ssize_t tcp_read(int fd, void *buf, size_t count);
ssize_t tcp_write(int fd, const void *buf, size_t count);

#endif
