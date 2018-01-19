#include "util.h"

Point create_point(float x, float y)
{
    Point new;
    new.x = x;
    new.y = y;

    return new;
}

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
