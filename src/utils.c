#include "math.h"

int modulus(int a, int b)
{
    return ((a %= b) < 0) ? a + b : a;
}