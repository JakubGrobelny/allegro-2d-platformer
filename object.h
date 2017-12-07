#include "sprite.h"
#include "hitbox.h"
#include "keyboard.h"
#include <stdbool.h>
#include "physics.h"

#ifndef _OBJECT
#define _OBJECT

typedef struct
{
    int pos_x;
    int pos_y;
    int width;
    int height;
    int type;
    // Komponenty:
    Hitbox hitbox;
    Sprite sprite;
    Physics physics;

} Object;

Object create_object(int pos_x, int pos_y, int width, int height, Physics physics, int type);
void draw_object(Object* object);
void update_player(Object* player, bool* key);

#endif
