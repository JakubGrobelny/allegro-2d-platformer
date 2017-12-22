#include "physics.h"

Physics create_physics(float speed_x, float speed_y, float mass)
{
    Physics new;
    Vector speed = create_vector(speed_x, speed_y);
    new.speed = speed;
    new.mass = mass;

    return new;
}

Vector create_vector(float x, float y)
{
    Vector new;
    new.x = x;
    new.y = y;

    return new;
}
