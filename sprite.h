// do celow testowych sprite bedzie po prostu primitivem
#ifndef _SPRITE
#define _SPRITE

#include <allegro5/allegro_primitives.h>
#include "defines.h"

typedef struct
{
    // TODO: sprite powinien przechowywac bitmape
    int pos_x;
    int pos_y;
    int width;
    int height;

} Sprite;

Sprite create_sprite(int pos_x, int pos_y, int width, int height); // TODO: dodac bitmape jako argument funkcji
void draw_sprite(Sprite sprite, int type);
#endif
