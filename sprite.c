#include "sprite.h"

Sprite create_sprite(int pos_x, int pos_y, int width, int height) // TODO: dodac bitmape jako argument funkcji
{
    Sprite new;
    new.pos_x = pos_x;
    new.pos_y = pos_y;
    new.width = width;
    new.height = height;

    return new;
    // TODO: zmieniac ta funkcje wraz z pojawianiem sie kolejnych elementow struktury sprite
}

void draw_sprite(Sprite* sprite)
{
    al_draw_filled_rectangle(sprite->pos_x, sprite->pos_y, sprite->pos_x + sprite->width, sprite->pos_y + sprite->height, DARK_BLUE);
}
