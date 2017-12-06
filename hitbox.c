#include "hitbox.h"
#include <math.h>

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
    if (first->type == rectangle && second->type == rectangle)
    {
        if (first->pos_x < second->pos_x + second->width &&
            first->pos_x + first->width > second->pos_x &&
            first->pos_y < second->pos_y + second->height &&
            first->pos_y + first->height > second->pos_y)
            return true;
    }
    if (first->type == circle && second->type == circle)
    {
        double r_sum = (double)(first->width) + (double)(second->width);
        double distance = sqrt((double)(first->pos_x - second->pos_x)*(first->pos_x - second->pos_x)+(double)(first->pos_y - second->pos_y)*(first->pos_y - second->pos_y));
        if (distance <= r_sum)
            return true;
    }
    else
    {
        // TODO: kolizja miedzy prostokatem a okregiem
    }
    return false;
}
