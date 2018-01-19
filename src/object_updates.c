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
    int direction_x;
    int direction_y;

    if (object->physics.speed.x == 0.0f)
        direction_x = STATIC;
    else if (object->physics.speed.x > 0.0f)
        direction_x = RIGHT;
    else
        direction_x = LEFT;

    if (object->physics.speed.y == 0.0f)
        direction_y = STATIC;
    else if (object->physics.speed.y > 0.0f)
        direction_y = BOTTOM;
    else
        direction_y = TOP;

    Point origin = create_point(object->hitbox.pos_x, object->hitbox.pos_y);
    Point target = create_point(origin.x + (int)object->physics.speed.x, origin.y + (int)object->physics.speed.y);
    Hitbox temp = object->hitbox;
    temp.pos_x = target.x;
    temp.pos_y = target.y;

    for (int i = 0; i < list->size; i++)
    {
        Object* obstacle = get_element_pointer_ol(list, i);

        if (collide(temp, obstacle->hitbox))
        {
            // how much overlap there is in ox and oy axes
            int delta_x = 0;
            int delta_y = 0;

            // calculating the overlaps and moving the target accordingly by substracting the overlap
            if (direction_x == RIGHT)
            {
                delta_x = temp.pos_x + temp.width - obstacle->hitbox.pos_x;

                if (delta_x < 0)
                    delta_x = 0;
            }
            else if (direction_x == LEFT)
            {
                delta_x = temp.pos_x - (obstacle->hitbox.pos_x + obstacle->hitbox.width);

                if (delta_x > 0)
                    delta_x = 0;
            }

            if (direction_x == TOP)
            {
                delta_y = temp.pos_y - (onstacle->hitbox.pos_y + obstacle->hitbox.height);

                if (delta_y > 0)
                    delta_y = 0;
            }
            else if (direction_y == BOTTOM)
            {
                delta_y = temp.pos_y + temp.height - obstacle->hitbox.pos_y;

                if (delta_y < 0)
                    delta_y = 0;
            }

            // TODO: finish

            target.x -= delta_x;
            target.y -= delta_y;
        }
    }

    object->pos_x = target.x;
    object->pos_y = target.y;
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
