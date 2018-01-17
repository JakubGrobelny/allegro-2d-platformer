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
        if ((first.pos_x + first.width < second.pos_x || first.pos_x > second.pos_x + second.width) ||
            (first.pos_y + first.height < second.pos_y || first.pos_y > second.pos_y + second.height))
            return false;
        return true;
    }
    if (first.type == CIRCLE && second.type == CIRCLE)
    {
        double r_sum = (double)(first.width) + (double)(second.width);
        double distance = sqrt((double)(first.pos_x - second.pos_x)*(first.pos_x - second.pos_x)+(double)(first.pos_y - second.pos_y)*(first.pos_y - second.pos_y));
        if (distance <= r_sum)
            return true;
    }
    else
    {
        double rect_x;
        double rect_y;
        double circle_x;
        double circle_y;
        double circle_r;
        double rect_width;
        double rect_height;

        if (first.type == RECTANGLE)
        {
            rect_x = (double)(first.pos_x);
            rect_y = (double)(first.pos_y);
            circle_x = (double)(second.pos_x);
            circle_y = (double)(second.pos_y);
            circle_r = (double)(second.width);
            rect_width = (double)(first.width);
            rect_height = (double)(first.height);
        }
        else
        {
            rect_x = (double)(second.pos_x);
            rect_y = (double)(second.pos_y);
            circle_x = (double)(first.pos_x);
            circle_y = (double)(first.pos_y);
            circle_r = (double)(first.width);
            rect_width = (double)(second.width);
            rect_height = (double)(second.height);
        }

        double nearest_x;
        double nearest_y;

        nearest_x = maximum(rect_x, minimum(circle_x, rect_x + rect_width));
        nearest_y = maximum(rect_y, minimum(circle_y, rect_y + rect_height));

        double distance_x;
        double distance_y;

        distance_x = circle_x - nearest_x;
        distance_y = circle_y - nearest_y;

        return (distance_x * distance_x + distance_y * distance_y) < (circle_r * circle_r);
    }
    return false;
}
