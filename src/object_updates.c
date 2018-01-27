#include "object_updates.h"

void apply_vectors(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH], ObjectsList* list)
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

    if (object->alive)
    {
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

                                if (object->type == PLAYER || object->type == PLAYER_BIG)
                                {
                                    Hitbox middle = new_y;
                                    middle.width = new_y.width - 48;
                                    middle.pos_x += 24;

                                    if (collide(middle, obstacle->hitbox))
                                    {
                                        if (obstacle->type == NORMAL_BLOCK)
                                        {
                                            if (object->type == PLAYER_BIG)
                                                break_block(obstacle, list);
                                            else
                                                bump_block(obstacle, list);
                                        }
                                        if (obstacle->type == SECRET_BLOCK)
                                        {
                                            spawn_coin(obstacle, list);
                                        }
                                        else if (obstacle->type == SECRET_BLOCK_MUSHROOM)
                                        {
                                            spawn_mushroom(obstacle, list);
                                        }
                                    }

                                }
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
    }

    object->pos_x += object->physics.speed.x;
    object->pos_y += object->physics.speed.y;

    if (object->alive)
    {
        handle_being_stuck(object, level, previous_pos_x, previous_pos_y);

        object->hitbox.pos_y = object->pos_y + (object->height - object->hitbox.height);
        object->hitbox.pos_x = object->pos_x + (object->width - object->hitbox.width) / 2;

        if (previous_speed_x != object->physics.speed.x)
        object->physics.speed.x = 0;
        if (previous_speed_y != object->physics.speed.y)
        object->physics.speed.y = 0;

        // SPECIAL OBJECT TYPES HANDLING
        if (object->type == ENEMY_GOOMBA || object->type == ENEMY_KOOPA || object->type == KOOPA_SHELL)
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
    x2 = (object->hitbox.pos_x + object->hitbox.width) / 64;

    y = (object->hitbox.pos_y + object->hitbox.height) / 64;

    if (x1 < 0 || x1 >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT || x2 < 0 || x2 >= MAP_WIDTH)
        return false;

    return (level[y][x1].type != EMPTY || level[y][x2].type != EMPTY);
}

void kill(Object* object, int i, ObjectsList* list)
{
    if (object->type == PARTICLE_NORMAL || object->type == ENEMY_KOOPA)
        pop_element_ol(list, i);
    else
    {
        Physics dead_enemy_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
        init_object(object, PARTICLE_NORMAL, object->pos_x, object->pos_y, object->width, object->height, RECTANGLE, object->hitbox.pos_x, object->hitbox.pos_y, object->hitbox.width, object->hitbox.height, dead_enemy_physics, object->frames_number);
        object->animation_frame = object->frames_number;
        object->counter = 30;
        object->alive = false;
    }
}

void animate_non_static_objects(ObjectsList* objects, int frame, Object* player)
{
    for (int i = 0; i < objects->size; i++)
    {
        Object* temp = get_element_pointer_ol(objects, i);

        if (distance_x(player, temp) <= RENDER_DISTANCE)
        {
            if (temp->type == ENEMY_GOOMBA)
            {
                if (frame % 12 == 0 && frame != 0)
                {
                    temp->animation_frame++;

                    if (temp->animation_frame >= temp->frames_number)
                    {
                        temp->animation_frame = 0;
                    }
                }
            }
            else if (temp->type == ENEMY_KOOPA)
            {
                if (temp->physics.speed.x > 0 && temp->animation_frame < 2)
                temp->animation_frame = 2;
                else if (temp->physics.speed.x < 0 && temp->animation_frame > 1)
                temp->animation_frame = 0;

                if (frame % 12 == 0 && frame != 0)
                {
                    temp->animation_frame++;

                    if (temp->physics.speed.x > 0)
                    {
                        if (temp->animation_frame > 3)
                        temp->animation_frame = 2;
                    }
                    else if (temp->physics.speed.x < 0)
                    {
                        if (temp->animation_frame > 1)
                        temp->animation_frame = 0;
                    }
                }
            }
        }
    }
}

void animate_static_objects(Object level[MAP_HEIGHT][MAP_WIDTH], int frame, Object* player)
{
    for (int height = 0; height < MAP_HEIGHT; height++)
    {
        for (int width = ((int)((player->pos_x - 1) / 64) - MAP_WIDTH); width <= ((int)((player->pos_x + player->width + 1) / 64) + MAP_WIDTH); width++)
        {
            if (width >= 0 && width < MAP_WIDTH)
            {
                if (level[height][width].frames_number > 1 && (frame % 30 == 0) && frame != 0)
                {
                    level[height][width].animation_frame++;

                    if (level[height][width].animation_frame >= level[height][width].frames_number)
                        level[height][width].animation_frame = 0;
                }
                else if (level[height][width].counter) // if bumped
                {
                    level[height][width].pos_y += level[height][width].physics.speed.y;
                    level[height][width].physics.speed.y += GRAV_CONST * 1.25f;

                    if (level[height][width].pos_y >= level[height][width].hitbox.pos_y)
                    {
                        level[height][width].pos_y = level[height][width].hitbox.pos_y;
                        level[height][width].physics.speed.y = 0.0f;
                        level[height][width].counter = 0;
                    }

                }
            }
        }
    }
}

void update_non_static_objects(ObjectsList* objects, Object level[MAP_HEIGHT][MAP_WIDTH], Object* player)
{
    for (int i = 0; i < objects->size; i++)
    {
        Object* object = get_element_pointer_ol(objects, i);

        if (distance_x(object, player) <= RENDER_DISTANCE) // only update objects that are close to the player
        {
            if (object->type == PARTICLE_NORMAL)
            {
                if (object->counter > 0)
                    object->counter--;
                else
                    kill(object, i, objects);
            }

            apply_vectors(object, level, objects);

            if (object->type == KOOPA_SHELL)
                check_for_shell_collisions(i, objects);
            else
            {
                for (int e = 0; e < objects->size; e++)
                {
                    if (e != i)
                    {
                        Object* temp = get_element_pointer_ol(objects, e);

                        if (temp->type != PARTICLE_NORMAL && temp->alive)
                        {
                            if (collide(object->hitbox, temp->hitbox))
                            object->physics.speed.x *= -1;
                        }
                    }
                }
            }

            if (object->pos_y > DISPLAY_HEIGHT)
                kill(object, i, objects);
        }
    }
}

void check_for_shell_collisions(int shell_index, ObjectsList* list)
{
    Object* shell = get_element_pointer_ol(list, shell_index);
    int size = list->size;

    for (int i = 0; i < size; i++)
    {
        if (i != shell_index)
        {
            Object* object = get_element_pointer_ol(list, i);

            if (distance_x(shell, object) < (int)(abs_float(shell->physics.speed.x) + 0.5f) + 10 && object->type != PARTICLE_NORMAL)
            {
                if (collide(shell->hitbox, object->hitbox))
                {
                    int dir_x = (shell->physics.speed.x > 0) ? RIGHT : (shell->physics.speed.x < 0 ? LEFT : STATIC);

                    if (dir_x != STATIC)
                    {
                        if (relative_direction(shell, object, dir_x))
                            kill(object, i, list);
                        // break; <- i guess it can only colide with one object at a time so checking every single one of them is not necessary
                    }
                }
            }
        }
    }
}

void spawn_shell(Object* enemy, ObjectsList* list)
{
    Object new_shell;
    Physics shell_physics = create_physics(0.0f, 0.0f, 13.0f, 0.0f, 2.0f);

    // shell is 60x48 vs koopa's 96x80

    bind_bitmap(&new_shell, enemy->bitmap);
    init_object(&new_shell, KOOPA_SHELL, enemy->pos_x, enemy->pos_y, 96, 80, RECTANGLE, enemy->pos_x + 18, enemy->pos_y + 32, 60, 48, shell_physics, 1);
    new_shell.animation_frame = 4;

    push_back_ol(list, new_shell);
}

void bump_block(Object* block, ObjectsList* list)
{
    kill_enemies_above_block(block, list);

    if (block->counter)
    {
        block->pos_y = block->hitbox.pos_y;
    }

    block->counter = 1; // 1 - bumped, 0 - not bumped
    block->physics.speed.y = BUMP_AMOUNT;

    //TODO play sound
}

void spawn_mushroom(Object* block, ObjectsList* list)
{
    bump_block(block, list);
    //TODO play sound
}

void spawn_coin(Object* block, ObjectsList* list)
{
    bump_block(block, list);

    //TODO play sound
}

void kill_enemies_above_block(Object* block, ObjectsList* list)
{
    // Killing enemies above
    Hitbox temp_hitbox;

    temp_hitbox.type = RECTANGLE;
    temp_hitbox.pos_x = block->hitbox.pos_x + 4;
    temp_hitbox.pos_y = block->hitbox.pos_y - block->hitbox.height;
    temp_hitbox.width = block->hitbox.width - 8;
    temp_hitbox.height = block->hitbox.height;

    for (int i = 0; i < list->size; i++)
    {
        Object* temp_obj = get_element_pointer_ol(list, i);

        if (collide(temp_hitbox, temp_obj->hitbox) && temp_obj->type != PARTICLE_NORMAL)
        {
            kill(temp_obj, i, list);
            i--;
        }
    }
}

void break_block(Object* block, ObjectsList* list)
{
    kill_enemies_above_block(block, list);

    //TODO play sound

    // Doing some object initiation magic to spawn 4 particles
    Physics static_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Object particle;
    Physics particle_physics = create_physics(-2.0f, -5.0f, 0.0f, 0.0f, 1.0f);
    bind_bitmap(&particle, block->bitmap);
    init_object(&particle, PARTICLE_NORMAL, block->pos_x - 24, block->pos_y - 24, 64, 64, RECTANGLE, block->pos_x, block->pos_y, 64, 64, particle_physics, 1);
    particle.counter = 300;
    particle.alive = false;
    particle.animation_frame = 1;
    push_back_ol(list, particle);
    particle.pos_y += 48;
    push_back_ol(list, particle);
    particle.pos_x += 48;
    particle_physics.speed.x *= -1;
    particle.physics = particle_physics;
    push_back_ol(list, particle);
    particle.pos_y -= 48;
    push_back_ol(list, particle);

    init_object(block, EMPTY, block->pos_x, block->pos_y, 64, 64, RECTANGLE, block->hitbox.pos_x, block->hitbox.pos_y, 64, 64, static_physics, 0);
    block->bitmap = NULL;
}
