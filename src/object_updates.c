#include "object_updates.h"

bool collides_in_direction(Object* object, Object level[], int direction)
{
    int x;
    int y;

    x = object->hitbox.pos_x / 64;
    y = object->hitbox.pos_y / 64;

// TODO: FINISH!!!1

    switch (direction)
    {
        case LEFT:
        case RIGHT:
        case TOP:
        case BOTTOM:
    }

    return false;
}

void apply_vectors(Object* object, Object level[])
{
    apply_gravity(object);

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

    // if (dir_y == BOTTOM)
    //      new_x.pos_y--;

    for (int i = 0; i < list->size; i++)
    {
        new_x.pos_y = object->hitbox.pos_y + (int)object->physics.speed.y; // TODO: tutaj cos zmienic

        if (relative_direction(object, get_element_pointer_ol(list, i), dir_x) || relative_direction(object, get_element_pointer_ol(list, i), dir_y))
        {
            //printf("speed_x = %f, speed_y = %f\n", object->physics.speed.x, object->physics.speed.y);

            Hitbox obstacle = get_element_pointer_ol(list, i)->hitbox;

            if (relative_direction(object, get_element_pointer_ol(list, i), TOP)) // fix for <-> + /\//
            {
                new_x.pos_y += 1;
            }
            else
            {
                new_x.pos_y -= 2;
            }
            // if (relative_direction(object, get_element_pointer_ol(list, i), BOTTOM)) // fix for <-> + \/
            // {
            // }

            if (collide(new_x, obstacle))
            {
                // adjust speed
                int adjustment = 0;

                if (dir_x == LEFT)
                {
                    adjustment = (obstacle.pos_x + obstacle.width) - new_x.pos_x + 1;
                    //printf("Adjustment_x_left = (%d + %d) - %d + 1 = %d\n", obstacle.pos_x, obstacle.width, new_x.pos_x, adjustment);
                }
                else if (dir_x == RIGHT)
                {
                    adjustment = obstacle.pos_x - (new_x.pos_x + new_x.width) - 1;
                    //printf("Adjustment_x_right = %d - (%d - %d) - 1 = %d\n", obstacle.pos_x, new_x.pos_x, new_x.width, adjustment);
                }

                if ((object->physics.speed.x + adjustment) * object->physics.speed.x > 0)
                    object->physics.speed.x += adjustment;
                else
                    object->physics.speed.x = 0;

            }
            if (collide(new_y, obstacle))
            {
                // adjust speed
                int adjustment = 0;

                if (dir_y == TOP)
                {
                    adjustment = (obstacle.pos_y + obstacle.height) - new_y.pos_y;
                    //printf("Adjustment_y_top = (%d + %d) - %d + 1 = %d\n", obstacle.pos_y, obstacle.width, new_y.pos_y, adjustment);
                }
                else if (dir_y == BOTTOM)
                {
                    adjustment = obstacle.pos_y - (new_y.pos_y + new_y.height);
                    //printf("Adjustment_y_bottom = %d - (%d - %d) - 1 = %d\n", obstacle.pos_y, new_y.pos_y, new_y.height, adjustment);
                }

                if ((object->physics.speed.y + adjustment) * object->physics.speed.y > 0)
                    object->physics.speed.y += adjustment;
                else
                    object->physics.speed.y = 0;

                //if (relative_direction(object, get_element_pointer_ol(list, i), TOP))
                //    new_x.pos_y -= 2;
            }
        }
    }

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

void kill(Object* object, int i, Object level[])
{
    printf("%d:\nBefore: ", i);

    for (int e = 0; e < list->size; e++)
    {
        printf("%d ", get_element_pointer_ol(list, e)->pos_x);
    }

    pop_element_ol(list, i);

    printf(" After: ");

    for (int e = 0; e < list->size; e++)
    {
        printf("%d ", get_element_pointer_ol(list, e)->pos_x);
    }
    putchar('\n');

    // TODO: play animation
}

void update_non_static_objects(ObjectsList* objects, Object level[])
{
    for (int i = 0; i < non_static_objects->size; i++)
    {
        Object* object = get_element_pointer_ol(non_static_objects, i);

        if (object->type == ENEMY_GOOMBA)
        {
            // TODO:
        }

        // TODO:
    }
}
