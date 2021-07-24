#include <stdio.h>
static int foo(int a)
{
	static int b = 5;
	int c;
	c = a * b;
	b += b;
	return c;
}

int main(int argc, char *argv[])
{
	printf("%d\n", foo(foo(1)));
	return foo(foo(1));
}