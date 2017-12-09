#include "object.h"

void init_object(Object* object, int pos_x, int pos_y, int width, int height, int hitbox_type, Physics physics)
{
    object->pos_x = pos_x;
    object->pos_y = pos_y;
    object->width = width;
    object->height = height;
    object->physics = physics;
    object->hitbox = create_hitbox(hitbox_type, pos_x, pos_y, width, height);
}

void bind_bitmap(Object* object, ALLEGRO_BITMAP* bitmap)
{
    object->bitmap = bitmap;
}

void draw_object(Object* object)
{
    al_draw_bitmap(object->bitmap, (float)object->pos_x, (float)object->pos_y, 0);
}
