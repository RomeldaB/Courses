/*
* hello-stdio.c --
*
*
This file contains a program which uses the stdio library to
*
print a short message. Note that we check the return code of
*
puts() and that we flush() the buffered output stream manually
*
to check whether writing to stdout actually worked.
*
* Exercise:
*
* On Linux, run the program with ltrace and strace. Explain the
* results produced by ltrace and strace.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	const char msg[] = "Hello World";
	int n;
	n = puts(msg);
	if (n == EOF) {
		return EXIT_FAILURE;
	}

	if (fflush(stdout) == EOF) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;	
}