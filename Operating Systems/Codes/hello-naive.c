/*
* hello-naive.c --
*
*
This file contains a naive program which uses the stdio
*
library to print a short message.
*
* Exercise:
*
* On Linux, run the program with ltrace and strace. Explain the
* results produced by ltrace and strace.
*/

#include <stdio.h>

int main()
{
	printf("Hello World\n");
	return 0;
}