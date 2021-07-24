/*
* hello-write.c --
*
*
This file contains a program which invokes the Linux write()
*
system call.
*
* Exercise:
*
* Statically Compile and run the program. Look at the assembler code
* generated (objdump -S write, or gcc -S).
*/

#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	const char msg[] = "Hello World\n";
	ssize_t n;

	n = write(STDOUT_FILENO, msg, sizeof(msg));
	if (n == -1 || n != sizeof(msg)) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}