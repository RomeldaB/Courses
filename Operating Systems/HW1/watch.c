#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	char opt, ch = 'l';
	char *ptr;
	int b = 0, e = 0, sec = 2;
	// Parsing the options
	while((opt = getopt(argc, argv, "+ebn:")) >= 0)
	{
		if(opt == 'e')
			e = 1;
		else if(opt == 'b')
			b = 1;
		else if(opt == 'n')
		{
			if((sec = atoi(optarg)) == 0)
				exit(EXIT_FAILURE);
		}
		else
			exit(EXIT_FAILURE);
	}
	// Preparing execvp arguments
	char *arr[argc];
	pid_t p1, p2;
	int k, S;
	for(k=0; optind < argc; optind++, k++)
		arr[k] = argv[optind];
	arr[k] = NULL;

	for( ; ; )
	{
		p1 = fork();
		// Child
		if(p1 == 0)
		{
			execvp(arr[0], arr);
			if(b)
			{
				if(printf("\a")==EOF)
					exit(EXIT_FAILURE);
			}
			if(e)
				exit(EXIT_FAILURE);
		}
		// Parent
		else if(p1>0)
		{
			p2 = waitpid(p1, &S, 0);
			if(WIFEXITED(S) && WEXITSTATUS(S) != 0)
			{
				if(b)
				{
					if(printf("\a")==EOF)
						exit(EXIT_FAILURE);
				}
				if(e)
					exit(EXIT_FAILURE);
			}
			if(p2 == -1)
				exit(EXIT_FAILURE);
		}
		// Error handling
		else if(p1 == -1)
			exit(EXIT_FAILURE);
		sleep(sec);
	}

	return 0;
}