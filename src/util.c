#include "util.h"

Point create_point(int x, int y)
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

float abs_int(int number)
{
    return (number > 0 ? number : -number);
}

int distance_x(Object* first, Object* second)
{
    return abs_int(first->pos_x - second->pos_x);
}
