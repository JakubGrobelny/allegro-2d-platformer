#include "util.h"

void reset_buttons(bool* down, bool* up, unsigned int size)
{
    for (int i = 0; i < size; i++)
    {
        down[i] = false;
        up[i] = false;
    }
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
