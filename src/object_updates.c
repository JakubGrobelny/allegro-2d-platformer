#include "object_updates.h"

void apply_vectors(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH])
{
    apply_gravity(object);

    int previous_speed_x = object->physics.speed.x;
    int previous_speed_y = object->physics.speed.y;

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

    int grid_height = abs_int((object->physics.speed.y / 64)) + 1;
    int grid_width = abs_int((object->physics.speed.x / 64)) + 1;

    for (int y = (object->hitbox.pos_y) / 64 - 1 - grid_height; y <= (object->hitbox.pos_y) / 64 + 1 + grid_height; y++)
    {
        for (int x = (object->hitbox.pos_x) / 64 - 1 - grid_width; x <= (object->hitbox.pos_x) / 64 + 1 + grid_width; x++)
        {
            if (y >= 0 && y < MAP_HEIGHT && x >= 0 && x < MAP_WIDTH)
            {
                Object* obstacle = &level[y][x];

                if (obstacle->type != EMPTY && (relative_direction(object, obstacle, dir_x) || relative_direction(object, obstacle, dir_y)))
                {
                    if (relative_direction(object, obstacle, TOP))
                    {
                        new_x.pos_y += 1;
                    }
                    else
                    {
                        new_x.pos_y -= 2;
                    }

                    if (collide(new_x, obstacle->hitbox))
                    {
                        // adjust speed
                        int adjustment = 0;

                        if (dir_x == LEFT)
                        {
                            adjustment = (obstacle->hitbox.pos_x + obstacle->hitbox.width) - new_x.pos_x + 1;
                            //printf("Adjustment_x_left = (%d + %d) - %d + 1 = %d\n", obstacle->hitbox.pos_x, obstacle->hitbox.width, new_x.pos_x, adjustment);
                        }
                        else if (dir_x == RIGHT)
                        {
                            adjustment = obstacle->hitbox.pos_x - (new_x.pos_x + new_x.width) - 1;
                            //printf("Adjustment_x_right = %d - (%d - %d) - 1 = %d\n", obstacle->hitbox.pos_x, new_x.pos_x, new_x.width, adjustment);
                        }

                        if ((object->physics.speed.x + adjustment) * object->physics.speed.x > 0)
                            object->physics.speed.x += adjustment;
                        else
                            object->physics.speed.x = 0;
                    }
                    if (collide(new_y, obstacle->hitbox))
                    {
                        // adjust speed
                        int adjustment = 0;

                        if (dir_y == TOP)
                        {
                            adjustment = (obstacle->hitbox.pos_y + obstacle->hitbox.height) - new_y.pos_y;
                            //printf("Adjustment_y_top = (%d + %d) - %d + 1 = %d\n", obstacle->hitbox.pos_y, obstacle->hitbox.width, new_y.pos_y, adjustment);
                        }
                        else if (dir_y == BOTTOM)
                        {
                            adjustment = obstacle->hitbox.pos_y - (new_y.pos_y + new_y.height);
                            //printf("Adjustment_y_bottom = %d - (%d - %d) - 1 = %d\n", obstacle->hitbox.pos_y, new_y.pos_y, new_y.height, adjustment);
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
        }
    }

    object->pos_x += object->physics.speed.x;
    object->pos_y += object->physics.speed.y;

    object->hitbox.pos_y = object->pos_y + (object->height - object->hitbox.height);
    object->hitbox.pos_x = object->pos_x + (object->width - object->hitbox.width) / 2;

    if (previous_speed_x != object->physics.speed.x)
        object->physics.speed.x = 0;
    if (previous_speed_y != object->physics.speed.y)
        object->physics.speed.y = 0;
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
    y = (object->hitbox.pos_y + object->hitbox.height) / 64;

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
            apply_vectors(object, level);

            if (object->pos_y > DISPLAY_HEIGHT)
                kill(object, i, objects);

            // TODO:
        }

        // TODO:
    }
}
