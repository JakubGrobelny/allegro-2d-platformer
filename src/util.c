#include "util.h"

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
