#include "object.h"

void init_object(Object* object, int type, int pos_x, int pos_y, int width, int height, int hitbox_type, int hitbox_pos_x, int hitbox_pos_y, int hitbox_width, int hitbox_height, Physics physics, short frames_number)
{
    object->alive = true;
    object->type = type;
    object->pos_x = pos_x;
    object->pos_y = pos_y;
    object->width = width;
    object->height = height;
    object->physics = physics;
    object->hitbox = create_hitbox(hitbox_type, hitbox_pos_x, hitbox_pos_y, hitbox_width, hitbox_height);
    object->animation_frame = 0;
    object->frames_number = frames_number;
}

void bind_bitmap(Object* object, ALLEGRO_BITMAP* bitmap)
{
    object->bitmap = bitmap;
}

void draw_object(Object* object, int screen_offset)
{
    al_draw_bitmap_region(object->bitmap, 0, object->height * object->animation_frame, object->width, object->height, (float)(object->pos_x - screen_offset), (float)object->pos_y, 0);
}

bool relative_direction(Object* observer, Object* object, int direction)
{

    if (direction == TOP)
    {
        return ((observer->hitbox.pos_y >= object->hitbox.pos_y + object->hitbox.height) || (observer->hitbox.pos_y + observer->hitbox.height >= object->hitbox.pos_y + observer->hitbox.height));
    }
    else if (direction == BOTTOM)
    {
        return ((observer->hitbox.pos_y + observer->hitbox.height <= object->hitbox.pos_y + object->hitbox.height) || (observer->hitbox.pos_y + observer->hitbox.height <= object->hitbox.pos_y));
    }
    else if (direction == RIGHT)
    {
        return ((observer->hitbox.pos_x + observer->hitbox.width <= object->hitbox.pos_x) || (observer->hitbox.pos_x <= object->hitbox.pos_x));
    }
    else if (direction == LEFT)
    {
        return ((observer->hitbox.pos_x >= object->hitbox.pos_x + object->hitbox.width) || (observer->hitbox.pos_x + observer->hitbox.width >= object->hitbox.pos_x + object->hitbox.width));
    }

    return false;
}

void terminate_velocity(Object* object)
{
    object->physics.speed.x = 0.0f;
    object->physics.speed.y = 0.0f;
}

bool stands_on(Object* object, Object* platform)
{
        // TODO
}
