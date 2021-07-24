#include <unistd.h>
int main(int argc, char *argv[])
{
int fds[2]; char *argv2[2] = { "./inc", NULL };
pipe(fds);
if (fork() == 0) {
dup2(fds[0], STDIN_FILENO);
execv("./inc", argv2);
}
if (fork() == 0) {
dup2(fds[0], STDIN_FILENO);
execv("./inc", argv2);
}
write(fds[1], "01", 2);
return 0;
}