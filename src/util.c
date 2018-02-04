#include "util.h"

bool compare_strings(char first[], char second[])
{
    if (strlen(first) != strlen(second))
        return false;

    for (int i = 0; i < strlen(first); i++)
        if (first[i] != second[i])
            return false;

    return true;
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
