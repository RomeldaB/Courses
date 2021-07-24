#include <string.h>

void foo(char *bar)
{
	char c[12];
	strcpy(c, bar);
}
// no bounds checking
int main(int argc, char *argv[])
{
	if (argv[1]) foo(argv[1]);
	return 0;
}