#include "object_updates.h"

// bool collides_in_direction(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH], int direction)
// {
//     int x;
//     int y;
//
//     x = object->hitbox.pos_x / 64;
//     y = object->hitbox.pos_y / 64;
//
// // TODO: FINISH!!!1
//
//     switch (direction)
//     {
//         case LEFT:
//         case RIGHT:
//         case TOP:
//         case BOTTOM:
//     }
//
//     return false;
//}

void apply_vectors(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH])
{
    if (!on_the_ground(object, level))
        apply_gravity(object);

    if (object->physics.speed.x == 0 && object->physics.speed.y == 0)
        return;
        // TODO: change to:
        // temporary y correction for x correction
        // x correction
        // y correction

    int grid_height = abs_int((object->physics.speed.y / 64)) + 1;
    int grid_width = abs_int((object->physics.speed.x / 64)) + 1;

    for (int y = (object->hitbox.pos_y) / 64 - 1 - grid_height; y <= (object->hitbox.pos_y) / 64 + 1 + grid_height; y++)
    {
        for (int x = (object->hitbox.pos_x) / 64 - 1 - grid_width; x <= (object->hitbox.pos_x) / 64 + 1 + grid_width; x++)
        {
            if (y >= 0 && y < MAP_HEIGHT && x >= 0 && x < MAP_WIDTH)
            {
                if (level[y][x].type != EMPTY)
                {
                    Hitbox new_y = object->hitbox;
                    new_y.pos_y += object->physics.speed.y;
                    new_y.pos_x += object->physics.speed.x;

                    Hitbox temp_object = level[y][x].hitbox;

                    if (collide(new_y, temp_object))
                    {
                        if (object->physics.speed.y > 0)
                        {
                            if ((new_y.pos_y + new_y.height) - temp_object.pos_y > 0)
                                object->physics.speed.y -= (new_y.pos_y + new_y.height) - temp_object.pos_y;
                        }
                        else if (object->physics.speed.y < 0)
                        {
                            if ((temp_object.pos_y + temp_object.height) - new_y.pos_y > 0)
                                object->physics.speed.y += (temp_object.pos_y + temp_object.height) - new_y.pos_y;
                        }
                    }

                    Hitbox new_x = object->hitbox;
                    new_x.pos_y += object->physics.speed.y;
                    new_x.pos_x += object->physics.speed.x;

                    if (collide(new_x, temp_object))
                    {
                        if (object->physics.speed.y > 0)
                        {
                            if ((new_x.pos_y + new_x.height) - temp_object.pos_y > 0)
                                object->physics.speed.y -= (new_x.pos_y + new_x.height) - temp_object.pos_y;
                        }
                        else if (object->physics.speed.y < 0)
                        {
                            if ((temp_object.pos_y + temp_object.height) - new_x.pos_y > 0)
                                object->physics.speed.y += (temp_object.pos_y + temp_object.height) - new_x.pos_y;
                        }
                    }
                }
            }
        }
    }

    object->pos_x += object->physics.speed.x;
    object->pos_y += object->physics.speed.y;
}

void apply_gravity(Object* object)
{
    object->physics.speed.y += object->physics.mass * GRAV_CONST;

    if (object->physics.speed.y > MAX_FALLING_SPEED)
        object->physics.speed.y = MAX_FALLING_SPEED;
}

bool on_the_ground(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH])
{
    int x1, x2;
    int y;

    x1 = object->hitbox.pos_x / 64;
    y = (object->hitbox.pos_y + object->hitbox.height)/ 64;

    x2 = (object->hitbox.pos_x + object->hitbox.width) / 64;

    if (x1 < 0 || x1 >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT || x2 < 0 || x2 >= MAP_WIDTH)
        return false;

    return (level[y][x1].type != EMPTY || level[y][x2].type != EMPTY);
}

void kill(Object* object, int i, ObjectsList* list)
{
    pop_element_ol(list, i);
    // TODO: play animation
}

void update_non_static_objects(ObjectsList* objects, Object level[MAP_HEIGHT][MAP_WIDTH])
{
    for (int i = 0; i < objects->size; i++)
    {
        Object* object = get_element_pointer_ol(objects, i);

        if (object->type == ENEMY_GOOMBA)
        {
            // TODO:
        }

        // TODO:
    }
}
