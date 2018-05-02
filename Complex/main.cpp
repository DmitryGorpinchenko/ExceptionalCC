#include "complex.h"

int main()
{
    Complex a = 1, b = 2, c = 3, d = 4;

    d = a + b + c;
    (a += b) = c;

    return 0;
}
