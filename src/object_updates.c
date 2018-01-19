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
    int pos_x = object->pos_x;
    int pos_y = object->pos_y;

    bool reset_speed_x = false;
    bool reset_speed_y = false;


    if (!collides_in_direction(object, list, ((object->physics.speed.y < 0.0f) ? BOTTOM : TOP)))
        pos_y += object->physics.speed.y;
    else
        reset_speed_y = true;
    if (!collides_in_direction(object, list, ((object->physics.speed.x > 0.0f) ? RIGHT : LEFT)))
        pos_x += object->physics.speed.x;
    else
        reset_speed_x = true;

    if (reset_speed_x)
        object->physics.speed.x = 0;
    if (reset_speed_y)
        object->physics.speed.y = 0;

    object->pos_x = pos_x;
    object->pos_y = pos_y;
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
