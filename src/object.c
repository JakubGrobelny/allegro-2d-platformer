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

void jump(Object* object)
{
        // TODO
}

bool stands_on(Object* object, Object* platform)
{
        // TODO
}
