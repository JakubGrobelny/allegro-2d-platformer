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

    if (direction_y == direction_x)
    {
        return;
    }

    Point origin = create_point(object->hitbox.pos_x, object->hitbox.pos_y);
    Point target = create_point(origin.x + (int)object->physics.speed.x + 0.5f, origin.y + (int)object->physics.speed.y + 0.5f);

    Hitbox temp = object->hitbox;
    temp.pos_x = object->hitbox.pos_x + (int)(object->physics.speed.x + 0.5f);
    temp.pos_y = object->hitbox.pos_y + (int)(object->physics.speed.y + 0.5f);

    for (int i = 0; i < list->size; i++)
    {
        Object* obstacle = get_element_pointer_ol(list, i);

        if (relative_direction(object, obstacle, direction_x) || relative_direction(object, obstacle, direction_y))
        {
            if (collide(temp, obstacle->hitbox))
            {
                //test
                printf("Collision!\n");

                // how much overlap there is in ox and oy axes
                int delta_x = 0;
                int delta_y = 0;

                // calculating the overlaps and moving the target accordingly by substracting the overlap
                if (direction_y == TOP)
                {
                    printf("TOP\n");
                    delta_y = temp.pos_y - (obstacle->hitbox.pos_y + obstacle->hitbox.height);

                }
                else if (direction_y == BOTTOM)
                {
                    printf("BOTTOM\n");
                    delta_y = temp.pos_y + temp.height - obstacle->hitbox.pos_y;

                }

                if (direction_x == RIGHT)
                {
                    printf("RIGHT\n");
                    delta_x = temp.pos_x + temp.width - obstacle->hitbox.pos_x;

                }
                else if (direction_x == LEFT)
                {
                    printf("LEFT\n");
                    delta_x = temp.pos_x - (obstacle->hitbox.pos_x + obstacle->hitbox.width);

                }

                if (delta_y = 0 && delta_x == 0)
                    break;
                else if (delta_y == 0)
                {
                    target.x -= delta_x;
                    object->physics.speed.x = 0.0f;
                    object->physics.speed.y = 0.0f;
                    break;
                }
                else if (delta_x == 0)
                {
                    target.y -= delta_y;
                    object->physics.speed.y = 0.0f;
                    object->physics.speed.x = 0.0f;
                    break;
                }

                if (abs_int(delta_x) > abs_int(delta_y))
                {
                    target.x -= delta_x;
                }
                else
                {
                    target.y -= delta_y;
                }

                float ratio;
                int full_length;
                int closer_length;

                if (abs_int(delta_x) >= abs_int(delta_y))
                {
                    full_length = abs_int(origin.x - temp.pos_x);
                    closer_length = abs_int(origin.x - (temp.pos_x - delta_x));
                    target.x -= delta_x;
                    ratio = (float)full_length / (float)closer_length;
                    delta_y *= (int)ratio;
                    target.y -= delta_y;
                }
                else
                {
                    full_length = abs_int(origin.y - temp.pos_y);
                    closer_length = abs_int(origin.y - (temp.pos_y - delta_y));
                    target.y -= delta_y;
                    ratio = (float)full_length / (float)closer_length;
                    delta_x *= (int)ratio;
                    target.x -= delta_x;
                }

                object->physics.speed.x = 0.0f;
                object->physics.speed.y = 0.0f;
            }
        }
    }

    object->pos_y = target.y - (object->height - object->hitbox.height) / 2;
    object->pos_x = target.x - (object->width - object->hitbox.width) / 2;
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
