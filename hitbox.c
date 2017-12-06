#include "hitbox.h"

Hitbox create_hitbox(short type, int pos_x, int pos_y, int width, int height)
{
    Hitbox new;
    new.type = type;
    new.pos_x = pos_x;
    new.pos_y = pos_y;
    new.width = width;
    new.height = height;

    return new;
}

bool collide(Hitbox* first, Hitbox* second)
{
    // TODO: zaimplementowac ta funkcje, tymczasowo sprawdza tylko czy hitboxy maja to samo polozenie
    if (first->pos_x == second->pos_x && first->pos_y == second->pos_y)
        return true;
    else
        return false;
}
