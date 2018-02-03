#include "hitbox.h"
#include <math.h>
#include "util.h"

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

bool collide(Hitbox first, Hitbox second)
{
    if (first.type == RECTANGLE && second.type == RECTANGLE)
    {
        if (first.pos_x + first.width < second.pos_x || first.pos_x > second.pos_x + second.width)
            return false;
        if (first.pos_y + first.height < second.pos_y || first.pos_y > second.pos_y + second.height)
            return false;

        return true;
    }

    return false;
}

void draw_hitbox(Hitbox hitbox, int screen_offset)
{
    al_draw_filled_rectangle(hitbox.pos_x - screen_offset, hitbox.pos_y + 16, hitbox.pos_x + hitbox.width - screen_offset, hitbox.pos_y + hitbox.height + 16, OPAQUE_RED);
}
