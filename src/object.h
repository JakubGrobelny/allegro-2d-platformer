#ifndef _OBJECT
#define _OBJECT

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "hitbox.h"
#include "keyboard.h"
#include <stdbool.h>
#include "physics.h"

typedef struct
{
    int pos_x;
    int pos_y;
    int type;

    ALLEGRO_BITMAP* bitmap;
    int width;
    int height;
    short animation_frame;
    short frames_number;

    // Komponenty:
    Hitbox hitbox;
    Physics physics;

} Object;

void init_object(Object* object, int pos_x, int pos_y, int width, int height, int hitbox_type, Physics physics, short frames_number);
void bind_bitmap(Object* object, ALLEGRO_BITMAP* bitmap);
void draw_object(Object* object);

#endif
