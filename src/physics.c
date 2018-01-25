#include "physics.h"

Physics create_physics(int speed_x, int speed_y, int acceleration_x, int acceleration_y, int mass)
{
    Physics new;
    Vector speed = create_vector(speed_x, speed_y);
    Vector acceleration = create_vector(acceleration_x, acceleration_y);
    new.speed = speed;
    new.acceleration = acceleration;
    new.mass = mass;

    return new;
}

Vector create_vector(int x, int y)
{
    Vector new;
    new.x = x;
    new.y = y;

    return new;
}
