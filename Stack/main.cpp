#include "stack.h"

int main()
{
    Stack<int> s;
    Stack<int> s1 = s;
    s = s1;
    return 0;
}
