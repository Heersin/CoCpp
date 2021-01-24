#include <stdlib.h>

/* *
 * intend to view the llvm
 * */

int foo(int arg)
{
    return arg + 1;
}

int main()
{
    int result;
    result = foo(5);
    result += 1;
    return 0;
}
