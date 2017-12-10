#include "physics.h"

Physics create_physics(float velocity_x, float velocity_y, float acceleration, bool gravity, float mass)
{
    Physics new;
    new.velocity_x = velocity_x;
    new.velocity_y = velocity_y;
    new.acceleration = acceleration;
    new.gravity = gravity;
    new.mass = mass;

    return new;
}

Physics generate_static_physics()
{
    return create_physics(0, 0, 0, false, 0);
}

void apply_gravity(Physics* physics)
{
    if (physics->velocity_y - GRAV_CONST >= MAX_FALL_SPEED)
        physics->velocity_y -= GRAV_CONST;
    else
        physics->velocity_y = MAX_FALL_SPEED;
}
