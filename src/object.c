#include "object.h"

void init_object(Object* object, int pos_x, int pos_y, int width, int height, int hitbox_type, Physics physics, short frames_number)
{
    object->pos_x = pos_x;
    object->pos_y = pos_y;
    object->width = width;
    object->height = height;
    object->physics = physics;
    object->hitbox = create_hitbox(hitbox_type, pos_x, pos_y, width, height);
    object->animation_frame = 0;
    object->frames_number = frames_number;
}

void bind_bitmap(Object* object, ALLEGRO_BITMAP* bitmap)
{
    object->bitmap = bitmap;
}

void draw_object(Object* object)
{
    al_draw_bitmap_region(object->bitmap, 0, object->height * object->animation_frame, object->width, object->height, (float)object->pos_x, (float)object->pos_y, 0);
}

bool relative_direction(Object* observer, Object* object, int direction)
{
    switch (direction)
    {
        case TOP:
            if (observer->pos_y <= object->pos_y + object->height)
                return true;
            break;
        case BOTTOM:
            if (observer->pos_y + observer->height >= object->pos_y)
                return true;
            break;
        case LEFT:
            if (observer->pos_x >= object->pos_x + object->width)
                return true;
            break;
        case RIGHT:
            if (observer->pos_x + observer->width <= object->width)
                return true;
            break;
    }

    return false;
}

void jump(Object* object)
{
        // TODO
}

bool stands_on(Object* object, Object* platform)
{
        // TODO
}
