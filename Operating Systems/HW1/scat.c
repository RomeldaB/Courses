#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sendfile.h>

int main(int argc, char *argv[])
{
	char opt, ch = 'l';
	char *ptr;
	// Parsing the options
	while((opt = getopt(argc, argv, "pls")) >= 0)
	{
		if(opt == 's')
			ch = opt;
		else if(opt == 'l')
			ch = opt;
		else if(opt == 'p')
			ch = opt;
		else
			exit(EXIT_FAILURE);
	}

	// The three loops
	if(ch == 's')
	{
		while(read(STDIN_FILENO, &ptr, 1))
		{
			if(ferror(stdin))
				exit(EXIT_FAILURE);
			if(!write(STDOUT_FILENO, &ptr, 1))
				exit(EXIT_FAILURE);
			if(ferror(stdout))
				exit(EXIT_FAILURE);
		}
	}

	if(ch == 'l')
	{
		while((ch = getc(stdin)) != EOF )
		{
			if(ferror(stdin))
				exit(EXIT_FAILURE);
			if(!putc(ch, stdout))
				exit(EXIT_FAILURE);
			if(ferror(stdout))
				exit(EXIT_FAILURE);
		}
	}

	if(ch == 'p')
	{
		off_t o = 0;
		while(sendfile(STDOUT_FILENO, STDIN_FILENO, &o, 4096))
		{
			if(fflush(stdin) == EOF)
				exit(EXIT_FAILURE);
		}

	}
	return 0;
}

/*
b.
The text file I used for testing is of size 11951281.
I get an average time of 0.154 seconds for the library 
loop and about 25.5 seconds for the system call loop.
Using strace we see that when using the sys call loop,
there are 11951281 calls of each read and write sys calls of
size 1, which explains the time it takes. Doing the same
for the other loops there are 2917 calls of read and write
(each) of size 4096, and one of size 3249, which explains why
it is faster.
c.
For the 3rd loop we get an everage time of 0.017 seconds,
so we observe that this loop is faster than the others. After
checking the documentation of the send file function, we see
that one of the reasons sendfile() is fast is becasue it doesn't
use a buffer.

*/