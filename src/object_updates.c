#include "object_updates.h"

void apply_vectors(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH])
{
    apply_gravity(object);

    float previous_speed_x = object->physics.speed.x;
    float previous_speed_y = object->physics.speed.y;
    int previous_pos_x = object->pos_x;
    int previous_pos_y = object->pos_y;

    Hitbox new_x = object->hitbox;
    Hitbox new_y = new_x;
    new_x.pos_x += object->physics.speed.x;
    new_y.pos_y += object->physics.speed.y;

    new_x.pos_y += 4;
    new_x.height -= 8;

    // new_y.pos_x += 4;
    // new_y.width -= 8;

    //draw_hitbox(new_x, 0);
    //draw_hitbox(new_y, 0);

    bool collision_right = false;
    bool collision_left = false;

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
                    if (collide(new_x, obstacle->hitbox))
                    {
                        // printf("Collided with (%d,%d) while going %s\n", obstacle->hitbox.pos_x / 64, obstacle->hitbox.pos_y / 64, dir_x == LEFT? "left" : "right");

                        // adjust speed
                        int adjustment = 0;

                        if (dir_x == LEFT)
                        {
                            collision_left = true;
                            adjustment = (obstacle->hitbox.pos_x + obstacle->hitbox.width) - new_x.pos_x + 1;
                            //printf("Adjustment_x_left = (%d + %d) - %d + 1 = %d\n", obstacle->hitbox.pos_x, obstacle->hitbox.width, new_x.pos_x, adjustment);
                        }
                        else if (dir_x == RIGHT)
                        {
                            collision_right = true;
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
                        //printf("Collided with (%d,%d) while going %s\n", obstacle->hitbox.pos_x / 64, obstacle->hitbox.pos_y / 64, dir_x == BOTTOM? "down" : "up");

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

    handle_being_stuck(object, level, previous_pos_x, previous_pos_y);

    object->hitbox.pos_y = object->pos_y + (object->height - object->hitbox.height);
    object->hitbox.pos_x = object->pos_x + (object->width - object->hitbox.width) / 2;

    if (previous_speed_x != object->physics.speed.x)
        object->physics.speed.x = 0;
    if (previous_speed_y != object->physics.speed.y)
        object->physics.speed.y = 0;

    // SPECIAL OBJECT TYPES HANDLING
    if (object->type == ENEMY_GOOMBA)
    {
        if (collision_left)
        {
            object->physics.speed.x = object->physics.acceleration.x;
        }
        else if (collision_right)
        {
            object->physics.speed.x = -object->physics.acceleration.x;
        }
    }
}

void handle_being_stuck(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH], int previous_pos_x, int previous_pos_y)
{
    if (level[object->hitbox.pos_y / 64 + 1][object->hitbox.pos_x / 64].type != EMPTY && previous_pos_y == object->pos_y && previous_pos_x == object->pos_x)
    {
        Object* temp = &level[object->hitbox.pos_y / 64 + 1][object->hitbox.pos_x / 64];

        if (temp->hitbox.pos_y < object->hitbox.pos_y + object->hitbox.height)
            object->pos_y += (temp->hitbox.pos_y - (object->pos_y + object->height));
    }
    if (level[object->hitbox.pos_y / 64 + 1][(object->hitbox.pos_x + object->hitbox.width) / 64].type != EMPTY && previous_pos_y == object->hitbox.pos_y && previous_pos_x == object->pos_x) // TODO: merge it with the if statement above
    {
        Object* temp = &level[object->hitbox.pos_y / 64 + 1][(object->hitbox.pos_x + object->hitbox.width) / 64];

        if (temp->hitbox.pos_y < object->hitbox.pos_y + object->hitbox.height)
            object->pos_y += (temp->hitbox.pos_y - (object->pos_y + object->height));
    }

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

void animate_non_static_objects(ObjectsList* objects, int frame)
{

}

void update_non_static_objects(ObjectsList* objects, Object level[MAP_HEIGHT][MAP_WIDTH])
{
    for (int i = 0; i < objects->size; i++)
    {
        Object* object = get_element_pointer_ol(objects, i);

        if (object->type == ENEMY_GOOMBA)
        {
            int x;
            int y;

            x = object->physics.speed.x > 0.0f ? (int)((object->hitbox.pos_x + object->hitbox.width) / 64) : (int)((object->hitbox.pos_x) / 64);
            y = object->hitbox.pos_y / 64;

            int dir_x = object->physics.speed.x > 0 ? RIGHT : LEFT;

            apply_vectors(object, level);
            //
            // if (dir_x == RIGHT)
            // {
            //     if (x >= 0 && x < MAP_WIDTH)
            //     {
            //         if (level[y][x].type != EMPTY)
            //             object->physics.speed.x = -object->physics.acceleration.x;
            //     }
            // }
            // else if (dir_x == LEFT)
            // {
            //     if (x >= 0 && x < MAP_WIDTH)
            //     {
            //         if (level[y][x].type != EMPTY)
            //             object->physics.speed.x = object->physics.acceleration.x;
            //     }
            // }

            if (object->pos_y > DISPLAY_HEIGHT)
                kill(object, i, objects);

            // TODO:
        }

        // TODO:
    }
}
