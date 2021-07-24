#include <stdio.h>

static int foo(int a)
{
    static int b = 5; // 2. b = 10
    int c;
    c = a * b; // 1. c = 5; 2. c = 5*10 = 50
    b += b; // 1. b = 10; 2. b = 20
    return c; // 1. foo = 5; 2. foo = 50
}

int main(int argc, char *argv[])
{
    printf("%d\n", foo(foo(1)));
    return foo(foo(1));
}

// Main idea: using static, the value of b is saved 
// from one call of the function to another.

/* 
data -> b
stack -> a, c, return address of foo()
*/

// ---------------------------------------------------------
// Overwriting a function return address on the stack

// #include <stdio.h>
// #include <string.h>
// void foo(char *bar)
// {
//     char c[12];
//     strcpy(c, bar);
//     printf("%s\n", c);
// }
// // no bounds checking
// int main(int argc, char *argv[])
// {
//     if (argv[1]) 
//         foo(argv[1]);
//     return 0;
// }