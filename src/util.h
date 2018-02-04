#include <stdbool.h>
#include <stdlib.h>

#ifndef _UTIL
#define _UTIL

#include "object.h"

// returns true if two strings are the same
bool compare_strings(char first[], char second[]);

// return the absolute value of a number
float abs_float(float number);

// return the absolute value of a number
float abs_int(int number);

// calculates the distance between two objects on the X axis
int distance_x(Object* first, Object* second);

#endif
