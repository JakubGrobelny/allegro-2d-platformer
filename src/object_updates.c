#include "object_updates.h"

bool collides_in_direction(Object* object, ObjectsList* list, int direction)
{
    for (int i = 0; i < list->size; i++)
    {
        if (relative_direction(object, get_element_pointer_ol(list, i), direction))
        {
            Hitbox temp = object->hitbox;

            // int += float !!!

            if (direction == BOTTOM)
            {
                temp.pos_y += (int)(object->physics.speed.y + 0.5f);
                temp.pos_x += (int)(object->physics.speed.x);
            }
            else if (direction == RIGHT)
            {
                temp.pos_x += (int)(object->physics.speed.x + 0.5f);
                temp.pos_y += (int)(object->physics.speed.y);

            }
            else if (direction == TOP)
            {
                temp.pos_y += (int)(object->physics.speed.y - 0.5f);
                temp.pos_x += (int)(object->physics.speed.x);
            }
            else if (direction == LEFT)
            {
                temp.pos_x += (int)(object->physics.speed.x - 0.5f);
                temp.pos_y += (int)(object->physics.speed.y);
            }


            if (collide(temp, get_element_pointer_ol(list, i)->hitbox))
            {
                //if (direction != BOTTOM)
                //    printf("%s Collision!\n", direction == RIGHT ? "right" : (direction == LEFT ? "left" : (direction == TOP ? "top" : "bottom")));
                //object->animation_frame = 14; for collision testing
                return true;
            }
        }
    }

    return false;
}

void apply_vectors(Object* object, ObjectsList* list)
{
    Hitbox new_x = object->hitbox;
    Hitbox new_y = new_x;
    new_x.pos_x += (int)object->physics.speed.x;
    new_y.pos_y += (int)object->physics.speed.y;

    int dir_x = STATIC;
    int dir_y = STATIC;

    if (object->physics.speed.x > 0)
        dir_x = RIGHT;
    else if (object->physics.speed.x < 0)
        dir_x = LEFT;

    if (object->physics.speed.y > 0)
        dir_y = BOTTOM;
    else if (object->physics.speed.y < 0)
        dir_y = TOP;

    if (dir_y == dir_x) // static
        return;


    if (dir_y != BOTTOM)
        new_x.pos_y--;
    if (dir_x == LEFT)
        new_y.pos_x++;
    if (dir_x == RIGHT)
        new_y.pos_x--;

    for (int i = 0; i < list->size; i++)
    {
        if (relative_direction(object, get_element_pointer_ol(list, i), dir_x) || relative_direction(object, get_element_pointer_ol(list, i), dir_y))
        {
            Hitbox obstacle = get_element_pointer_ol(list, i)->hitbox;

            if (collide(new_x, obstacle))
            {
                // adjust speed
                int adjustment = 0;

                if (dir_x == LEFT)
                {
                    adjustment = (obstacle.pos_x + obstacle.width) - new_x.pos_x;
                }
                else if (dir_x == RIGHT)
                {
                    adjustment = obstacle.pos_x - (new_x.pos_x + new_x.width);
                    printf("adjustment_x_RIGHT = %d - (%d + %d) = %d, speed = %f\n", obstacle.pos_x, new_x.pos_x, new_x.width, adjustment, object->physics.speed.x);
                }

                object->physics.speed.x += adjustment;
            }
            if (collide(new_y, obstacle))
            {
                // adjust speed
                int adjustment = 0;

                if (dir_y == TOP)
                {
                    printf("adjustment_y_TOP = (%d + %d) - %d = %d, speed = %f\n", obstacle.pos_y, obstacle.height, new_y.pos_y, adjustment, object->physics.speed.y);
                    adjustment = (obstacle.pos_y + obstacle.height) - new_y.pos_y;
                }
                else if (dir_y == BOTTOM)
                {
                    printf("adjustment_y_BOTTOM = %d - (%d + %d) = %d, speed = %f\n", obstacle.pos_y, new_y.pos_y, new_y.width, adjustment, object->physics.speed.y);
                    adjustment = obstacle.pos_y - (new_y.pos_y + new_y.height);
                }

                object->physics.speed.y += adjustment;
            }
        }
    }

    printf("speed.x = %f, speed.y = %f\n", object->physics.speed.x, object->physics.speed.y);

    object->pos_x += (int)object->physics.speed.x;
    object->pos_y += (int)object->physics.speed.y;
}

void apply_gravity(Object* object)
{
    object->physics.speed.y += object->physics.mass * GRAV_CONST;

    if (object->physics.speed.y > MAX_FALLING_SPEED)
        object->physics.speed.y = MAX_FALLING_SPEED;
}

bool on_the_ground(Object* object, ObjectsList* list)
{
    return collides_in_direction(object, list, BOTTOM); // TODO: if object on list is platform
}
