#include <stdbool.h>

#ifndef _PHYSICS
#define _PHYSICS

typedef struct
{
    float x;
    float y;

} Vector;

typedef struct
{
    Vector speed;
    float mass;

} Physics;

Physics create_physics(float speed_x, float speed_y, float mass);
Vector create_vector(float x, float y);

#endif
