#include "object.h"

Object create_object(int pos_x, int pos_y, int width, int height, Physics physics, int type)
{
    Object new;
    new.pos_x = pos_x;
    new.pos_y = pos_y;
    new.height = height;
    new.width = width;
    new.physics = physics;
    new.hitbox = create_hitbox(type, pos_x, pos_y, width, height);
    new.sprite = create_sprite(pos_x, pos_y, width, height);
    new.type = type;

    return new;
}

void draw_object(Object object)
{
    draw_sprite(object.sprite, object.type);
}
