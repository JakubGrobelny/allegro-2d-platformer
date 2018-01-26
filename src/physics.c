#include "physics.h"

Physics create_physics(float speed_x, float speed_y, float acceleration_x, float acceleration_y, float mass)
{
    Physics new;
    Vector speed = create_vector(speed_x, speed_y);
    Vector acceleration = create_vector(acceleration_x, acceleration_y);
    new.speed = speed;
    new.acceleration = acceleration;
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
