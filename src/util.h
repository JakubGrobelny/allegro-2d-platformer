#ifndef _UTIL
#define _UTIL

typedef struct Point
{
    /*
    Structure representing a (x, y) point in space
     */

    int x;
    int y;

} Point;

// return the maximum of two numbers
double maximum(double a, double b);

// return the minimum of two numbers
double minimum(double a, double b);

// return the absolute value of a number
float abs_float(float number);

// return the absolute value of a number
float abs_int(int number);

// create new point (x, y)
Point create_point(int x, int y)

#endif
