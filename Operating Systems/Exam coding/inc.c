#include <unistd.h>
int main(int argc, char *argv[])
{
char buf[1];
read(STDIN_FILENO, buf, 1);
buf[0]++;
write(STDOUT_FILENO, buf, 1);
return 0;
}