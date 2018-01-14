#include "object_updates.h"

bool collides_in_direction(Object* object, ObjectsList* list, int direction)
{
    for (int i = 0; i < list->size; i++)
    {
        if (relative_direction(object, get_element_pointer_ol(list, i), direction))
        {
            Hitbox temp = object->hitbox;
            temp.pos_x += object->physics.speed.x;
            temp.pos_y += object->physics.speed.y;

            if (collide(object->hitbox, get_element_pointer_ol(list, i)->hitbox))
            {
                switch (direction)
                {
                    case TOP:
                        object->pos_y = get_element_pointer_ol(list, i)->pos_y + get_element_pointer_ol(list, i)->height;
                        break;
                    case BOTTOM:
                        object->pos_y = get_element_pointer_ol(list, i)->pos_y - object->height;
                        break;
                    case LEFT:
                        object->pos_x = get_element_pointer_ol(list, i)->pos_x + get_element_pointer_ol(list, i)->width;
                        break;
                    case RIGHT:
                        object->pos_x = get_element_pointer_ol(list, i)->pos_x - object->width;
                        break;
                }

                return true;
            }
        }
    }

    return false;
}

void apply_vectors(Object* object, ObjectsList* list)
{
    if (!collides_in_direction(object, list, (object->physics.speed.x > 0 ? RIGHT : LEFT)))
        object->pos_x += object->physics.speed.x;
    if (!collides_in_direction(object, list, (object->physics.speed.y > 0 ? TOP : BOTTOM)))
        object->pos_y += object->physics.speed.y;
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
