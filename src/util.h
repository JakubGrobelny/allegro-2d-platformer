#ifndef _UTIL
#define _UTIL

typedef struct Point
{
    /*
    Structure representing a (x, y) point in space
     */

    float x;
    float y;

} Point;

// return the maximum of two numbers
double maximum(double a, double b);

// return the minimum of two numbers
double minimum(double a, double b);

// return the absolute value of a number
float abs_float(float number);

// create new point (x, y)
Point create_point(float x, float y)

#endif
