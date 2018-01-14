#include "util.h"

double maximum(double a, double b)
{
    if (a > b)
        return a;
    return b;
}

double minimum(double a, double b)
{
    if (a < b)
        return a;
    return b;
}

float abs_float(float number)
{
    return (number > 0 ? number : -number);
}
