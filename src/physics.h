#include <stdbool.h>

#ifndef _PHYSICS
#define _PHYSICS

#define GRAV_CONST 10.0f
#define MAX_FALL_SPEED -20.0f

typedef struct
{
    float velocity_x;
    float velocity_y;
    float acceleration;
    bool gravity;
    float mass;

} Physics;

Physics generate_static_physics();
Physics create_physics(float velocity_x, float velocity_y, float acceleration, bool gravity, float mass);
void apply_gravity(Physics* physics);

#endif
