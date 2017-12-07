#include "physics.h"

Physics create_physics(int velocity_x, int velocity_y, int acceleration, bool gravity, int mass)
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
