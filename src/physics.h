#include <stdbool.h>

#ifndef _PHYSICS
#define _PHYSICS

#define GRAV_CONST          1  // gravitational constant
#define MAX_SPEED           20 // speed limit of objects
#define MAX_FALLING_SPEED   20 // speed limit of falling objects

typedef struct
{
    /*
    Structure representing a 2D vector
     */

    int x; // vector's x coordinate
    int y; // vector's y coordinate

} Vector;

typedef struct
{
    /*
    Structure responsible for holding physical properties of an object
     */

    Vector speed;         // 2D vector representing object's speed
    Vector acceleration;  // 2D vector representing object's acceleration that is applied when the object starts moving
    int mass;           // object's mass

} Physics;

// creating new Physics structure with given attributes
Physics create_physics(int speed_x, int speed_y, int acceleration_x, int acceleration_y, int mass);

// creating new Vector structure with given attributes
Vector create_vector(int x, int y);

#endif
