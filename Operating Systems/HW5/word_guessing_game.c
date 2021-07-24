#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>
#include <event2/event.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>
#include "state.h"

static struct event_base *b; //event base
static Connection *connections = NULL;

// Function to hide a word in the fortune sentence
static void transform(State* current) {
	char *word = NULL, *position;
	char temp[64];
	int x, pos;

	for(position = current->fortune; (position = strpbrk(position, ".,_!;-~`\n\t\v\f\r ")); position++, x++);
	
	srand(time(0));
	while(word == NULL){	
		strcpy(temp, current->fortune);
		word = strtok(temp, ".,_!;-~`\n\t\v\f\r ");
		pos = rand()%x;
		x = 0;
		while(word){
			if(x == pos){
		    	position = strstr(current->fortune, word);
		    	if(!position)
		       		break;
			    memset(position, '_', strlen(word));
			    strcpy(current->missing, word);
			    break;
			}
			word = strtok(NULL, ".,_!;-~`\n\t\v\f\r "), x++;
		}
	}
}

// Function to send a message to the client, represented by the connection struct
static void write_message(Connection* connection, int sms){
	char buffer[128];
	State* s = connection->state;
	switch(sms) {
		case 0:
			sprintf(buffer, "C: %s", s->fortune);
			break;
		case 1:
			strcpy(buffer, "Congratulation - challenge passed!\n");
			break;
		case 2:
			sprintf(buffer, "Wrong guess - expected: %s\n", s->missing);
			break;
		case 3:
			strcpy(buffer, "Command not found!\n");
			break;
		case 4:
			sprintf(buffer, "M: You mastered %d/%d challenges. Good bye!\n", s->correct, s->guesses_number);
			break;
	}
	if(tcp_write(connection->sock, buffer, strlen(buffer)) < 0) {
	 	fprintf(stderr, "Writing error!\n");
	 	exit(EXIT_FAILURE);
	}
}

static void fortune_transform(evutil_socket_t evfd, short evwhat, void *evarg){
	int len;
	Connection *current = (Connection*) evarg;
	char arr[64]; // 64 instead of 32 just to be sure there is enough space

	len = read(evfd, arr, 32);
	if(len || len == 0){
		// Make sure line ends at len
		arr[len] = '\0';
		// copy value to the fortune of the connections game
	  	strcpy(current->state->fortune, arr);
	} else {
	  	fprintf(stderr, "Reading error!\n");
	  	exit(EXIT_FAILURE);
	}
	// replace random word with _
	transform(current->state);
	write_message(current, 0);
}

// 
static void fortune_pipe(Connection* connection){
	// init pipe
	int pfd[2];
	pipe(pfd);

	// create and add event for transform fortune function
	struct event *fev = event_new(b, pfd[0], EV_READ, fortune_transform, connection);
	event_add(fev, NULL);

	// fork
	pid_t pid;
	if((pid = fork())  == 0){
	  	close(pfd[0]); //close read end
	  	dup2(pfd[1], STDOUT_FILENO);
	  	close(pfd[1]); //close write end
	  	execlp("fortune", "fortune", "-n", "32", "-s", NULL);
	  	exit(EXIT_FAILURE);
	} else if(pid > 0){
	    close(pfd[1]);
	}else {
		// empty string
	  	connection->state->fortune[0] = '\0';
	}
}

static void read_client(evutil_socket_t evfd, short evwhat, void *evarg){
	char *answer;
	int fd = evfd;
	char buffer[128];
	Connection *current = (Connection*) evarg;
	
	if(read(fd, buffer, sizeof(buffer)) < 0){
	  	fprintf(stderr, "Reading error!\n");
	  	exit(EXIT_FAILURE);
	}

	if(strstr(buffer, "Q:") == buffer){
		// send proper message and close connection
	  	write_message(current, 4);
	  	event_free(current->ev);
	  	tcp_close(fd);
	  	remove_connection(&connections, fd);
	} else {
	  	if(strstr(buffer, "R:") == buffer){
	  		// check if guess is correct
	        current->state->guesses_number++;
	     	memmove(buffer, buffer+2, strlen(buffer)-2);
	     	answer = strtok(buffer, ".,_!;-~`\n\t\v\f\r ");
	     	if(strcmp(answer, current->state->missing) != 0){
	        	write_message(current, 2);
	    	} else {
	        	current->state->correct++;
	        	write_message(current, 1);
	    }
	    fortune_pipe(current);
		} else {
	       	write_message(current, 3);
	  	}
	}
}

static void start(evutil_socket_t evfd, short evwhat, void *evarg){
	Connection *new_client;
	char str[128]= "M: Guess the missing ____!\nM: Send your guess in the for 'R: word\\r\\n'.\n";

	int fd;
	if((fd = tcp_accept((int)evfd)) < 0){
	  	fprintf(stderr, "Connection error!\n");
	  	exit(EXIT_FAILURE);
	}

	long int w = tcp_write(fd, str, strlen(str));
	if(w < 0){
	  	fprintf(stderr, "Writing error!\n");
	  	tcp_close(fd);
	  	exit(EXIT_FAILURE);
	}

	new_client = add_connection(&connections, fd);
	new_client->ev = event_new(b, fd, EV_READ | EV_PERSIST, read_client, new_client);
	event_add(new_client->ev, NULL);
	fortune_pipe(new_client);
}

// the main event loop is similar to the professor's implementations in the source codes (same as tcp funcs)
int main(int argc, char* argv[]){

	int fds;
	struct event *tev;
	/* In case "localhost" does not work, NULL should work */
	const char* interfaces[] = {"localhost", NULL, "0.0.0.0", "::"};

	if(argc != 2){
	  	fprintf(stderr, "Add [port]\n");
	  	exit(EXIT_FAILURE);
	}

	(void) daemon(0, 0);

	openlog("word_guessing_game", LOG_PID, LOG_DAEMON);
	// create event base
	b = event_base_new();
	if(!b){
	  	syslog(LOG_ERR, "Event creation error!\n");
	  	exit(EXIT_FAILURE);
	}

	for(int i = 0; interfaces[i]; i++){
	  	fds = tcp_listen(interfaces[i], argv[1]);
	  	if(fds > -1){
	    	tev = event_new(b, fds, EV_READ | EV_PERSIST, start, NULL);
	  		event_add(tev, NULL);
	  	}
	}

	if(event_base_loop(b, 0) == -1){
	  	syslog(LOG_ERR, "Event loop error!\n");
	  	event_base_free(b);
	  	exit(EXIT_FAILURE);
	}

	closelog();
	event_base_free(b);

	return EXIT_SUCCESS;
}