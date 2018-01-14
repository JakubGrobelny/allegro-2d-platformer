#include <stdbool.h>

#ifndef _PHYSICS
#define _PHYSICS

#define GRAV_CONST          1.0f  // gravitational constant
#define MAX_SPEED           12.0f // speed limit of objects
#define MAX_FALLING_SPEED   20.0f // speed limit of falling objects

typedef struct
{
    /*
    Structure representing a 2D vector
     */

    float x; // vector's x coordinate
    float y; // vector's y coordinate

} Vector;

typedef struct
{
    /*
    Structure responsible for holding physical properties of an object
     */

    Vector speed;         // 2D vector representing object's speed
    Vector acceleration;  // 2D vector representing object's acceleration that is applied when the object starts moving
    float mass;           // object's mass

} Physics;

// creating new Physics structure with given attributes
Physics create_physics(float speed_x, float speed_y, float acceleration_x, float acceleration_y, float mass);

// creating new Vector structure with given attributes
Vector create_vector(float x, float y);

#endif
