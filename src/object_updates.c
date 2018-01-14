#include "object_updates.h"

bool collides_in_direction(Object* object, ObjectsList* list, int direction)
{
    for (int i = 0; i < list->size; i++)
    {
        if (relative_direction(object, get_element_pointer_ol(list, i), direction))
        {
            if (collide(object->hitbox, get_element_pointer_ol(list, i)->hitbox))
                return true;
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
    // TODO: if not on_the_ground()

    object->physics.speed.y += object->physics.mass * GRAV_CONST;

    if (object->physics.speed.y > MAX_FALLING_SPEED)
        object->physics.speed.y = MAX_FALLING_SPEED;
}

bool on_the_ground(Object* object, ObjectsList* list)
{

}
