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

    int grid_height = abs_int((object->physics.speed.y / 64)) + 2;
    int grid_width = abs_int((object->physics.speed.x / 64)) + 2;

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

    // check if player is not leaving the map
    if (object->type == PLAYER || object->type == PLAYER_BIG)
    {
        if (object->pos_x < 0)
        {
            object->pos_x = 0;
            object->physics.speed.x = 0.0f;
        }
        else if (object->pos_x + object->width > MAP_WIDTH * 64)
        {
            object->pos_x = (MAP_WIDTH * 64) - object->width;
            object->physics.speed.x = 0.0f;
        }
    }

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
        if (object->type == ENEMY_GOOMBA || object->type == ENEMY_KOOPA || object->type == KOOPA_SHELL || object->type == SIZE_MUSHROOM || object->type == ENEMY_KOOPA_FLYING)
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
    int y = object->hitbox.pos_y / 64 + 1;
    int x = object->hitbox.pos_x / 64;

    if (y < 0 || y > MAP_HEIGHT)
        return;

    if (x >= 0 && x < MAP_WIDTH)
    {
        if (level[object->hitbox.pos_y / 64 + 1][object->hitbox.pos_x / 64].type != EMPTY && previous_pos_y == object->pos_y && previous_pos_x == object->pos_x)
        {
            Object* temp = &level[object->hitbox.pos_y / 64 + 1][object->hitbox.pos_x / 64];

            if (temp->hitbox.pos_y < object->hitbox.pos_y + object->hitbox.height)
            object->pos_y += (temp->hitbox.pos_y - (object->pos_y + object->height));
        }
    }

    x += object->hitbox.width;

    if (x >= 0 && x < MAP_WIDTH)
    {
        if (level[object->hitbox.pos_y / 64 + 1][(object->hitbox.pos_x + object->hitbox.width) / 64].type != EMPTY && previous_pos_y == object->hitbox.pos_y && previous_pos_x == object->pos_x) // TODO: merge it with the if statement above
        {
            Object* temp = &level[object->hitbox.pos_y / 64 + 1][(object->hitbox.pos_x + object->hitbox.width) / 64];

            if (temp->hitbox.pos_y < object->hitbox.pos_y + object->hitbox.height)
            object->pos_y += (temp->hitbox.pos_y - (object->pos_y + object->height));
        }
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
    // if (object->pos_y >= MAP_HEIGHT && object->pos_x > 0)
    // printf("An object of type %d was killed. It's index was %d\n", object->type, i);

    if (object->type == PARTICLE_NORMAL || object->type == ENEMY_KOOPA || object->type == SIZE_MUSHROOM || object->type == ENEMY_KOOPA_FLYING || object->type == KOOPA_SHELL || object->type == COIN)
        pop_element_ol(list, i);
    else
    {
        float previous_speed = object->physics.speed.x; // just for bullets
        int previous_type = object->type;
        Physics dead_enemy_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
        init_object(object, PARTICLE_NORMAL, object->pos_x, object->pos_y, object->width, object->height, RECTANGLE, object->hitbox.pos_x, object->hitbox.pos_y, object->hitbox.width, object->hitbox.height, dead_enemy_physics, object->frames_number);
        if (previous_type != BULLET)
        {
            object->animation_frame = object->frames_number;
            object->counter = 120;
        }
        else
        {
            object->animation_frame = previous_speed > 0.0f ? 2 : 3;
            object->counter = 30;
        }
        object->alive = false;
    }
}

void animate_non_static_objects(ObjectsList* objects, int frame, Object* player)
{
    int size = objects->size;
    for (int i = 0; i < size; i++)
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
            else if (temp->type == ENEMY_KOOPA || temp->type == ENEMY_KOOPA_FLYING)
            {
                int offset = temp->type == ENEMY_KOOPA_FLYING ? 5 : 0;

                if (temp->physics.speed.x > 0 && temp->animation_frame < 2 + offset)
                    temp->animation_frame = 2 + offset;
                else if (temp->physics.speed.x < 0 && temp->animation_frame > 1 + offset)
                    temp->animation_frame = 0 + offset;

                if (frame % 12 == 0 && frame != 0)
                {
                    temp->animation_frame++;

                    if (temp->physics.speed.x > 0)
                    {
                        if (temp->animation_frame > 3 + offset)
                            temp->animation_frame = 2 + offset;
                    }
                    else if (temp->physics.speed.x < 0)
                    {
                        if (temp->animation_frame > 1 + offset)
                            temp->animation_frame = 0 + offset;
                    }
                }
            }
            else if (temp->type == ENEMY_PIRANHA_PLANT)
            {
                if (frame % 6 == 1)
                {
                    if (temp->counter < 240)
                    {
                        temp->animation_frame = 0;
                    }
                    else if (temp->counter < 247 || temp->counter > 353)
                    {
                        temp->animation_frame = 1;
                    }
                    else
                    {
                        temp->animation_frame++;

                        if (temp->animation_frame > 3)
                            temp->animation_frame = 2;
                    }
                }
            }
        }
    }
}

void animate_static_objects(Object level[MAP_HEIGHT][MAP_WIDTH], int frame, Object* player, ObjectsList* list)
{
    for (int height = 0; height < MAP_HEIGHT; height++)
    {
        for (int width = ((int)((player->pos_x - 1) / 64) - MAP_WIDTH); width <= ((int)((player->pos_x + player->width + 1) / 64) + MAP_WIDTH); width++)
        {
            if (width >= 0 && width < MAP_WIDTH)
            {
                if (level[height][width].type == CANNON_LEFT || level[height][width].type == CANNON_RIGHT)
                {
                    if (distance_x(player, &level[height][width]) <= RENDER_DISTANCE)
                        fire_from_cannon(&level[height][width], list);
                    continue;
                }

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
    int size = objects->size;
    for (int i = 0; i < size; i++)
    {
        Object* object = get_element_pointer_ol(objects, i);

        if (distance_x(object, player) <= RENDER_DISTANCE && object->type != COIN) // only update objects that are close to the player
        {
            if (object->type == PARTICLE_NORMAL)
            {
                if (object->counter > 0)
                {
                    object->counter--;
                    apply_vectors(object, level, objects);
                    continue;
                }
                else
                {
                    kill(object, i, objects);
                    i--;
                    size--;
                    continue;
                }
            }
            else if (object->type == ENEMY_PIRANHA_PLANT)
            {
                object->counter++;
                // (0; 240) - hidden, (240, 360) - outside
                if (object->counter == 360)
                    object->counter = 0;
            }
            else if (object->type == ENEMY_KOOPA)
            {
                if (object->counter > 0)
                    object->counter--;
            }

            if (object->type != BULLET && object->type != COIN)
                apply_vectors(object, level, objects);
            else if (object->type == BULLET)
            {
                object->pos_x += object->physics.speed.x;
                object->hitbox.pos_x += object->physics.speed.x;
            }

            if (object->type == ENEMY_KOOPA_FLYING)
            {
                if (object->physics.speed.y >= object->physics.acceleration.y)
                    object->physics.speed.y = -object->physics.acceleration.y;
            }

            if (object->type == KOOPA_SHELL)
                check_for_shell_collisions(i, objects);
            else
            {
                for (int e = 0; e < size; e++)
                {
                    if (e != i)
                    {
                        Object* temp = get_element_pointer_ol(objects, e);

                        if (temp->alive)
                        {
                            if (collide(object->hitbox, temp->hitbox))
                            {
                                if (object->type != ENEMY_PIRANHA_PLANT && object->type != BULLET)
                                {
                                    Hitbox temp_bottom = object->hitbox;
                                    temp_bottom.height -= (object->hitbox.height - 1);
                                    temp_bottom.pos_y += (object->hitbox.height - 1);

                                    if (temp_bottom.pos_y + temp_bottom.height < temp->hitbox.pos_y + (temp->hitbox.height) / 2)
                                        object->physics.speed.y = -10.0f;
                                    else
                                        object->physics.speed.x *= -1;
                                }
                                else if (object->animation_frame > 1 || object->type == BULLET)
                                {
                                    //printf("Killed by a bullet i=%d e=%d type_bullet=%d (%d, %d) type_killed=%d (%d, %d)\n", i, e, object->type, object->pos_x, object->pos_y, temp->type, temp->pos_x, temp->pos_y);

                                    if (temp->type == ENEMY_KOOPA_FLYING)
                                        spawn_koopa(temp, objects);
                                    else if (temp->type == ENEMY_KOOPA && !temp->counter)
                                        spawn_shell(temp, objects);

                                    if (is_actually_killed(object))
                                        size--;
                                    kill(object, i, objects);

                                    if (temp->type != ENEMY_KOOPA || !temp->counter)
                                    {
                                        kill(temp, e, objects);

                                        if (e < i)
                                            if (is_actually_killed(temp))
                                                i--;
                                        if (is_actually_killed(temp))
                                        {
                                            e--;
                                            size--;
                                        }
                                    }

                                    break;
                                }
                            }
                        }
                    }
                }
            }

            if (object->hitbox.pos_y > DISPLAY_HEIGHT || object->hitbox.pos_x + object->hitbox.width < 0 || object->hitbox.pos_y + object->hitbox.height < 0 || object->hitbox.pos_x + object->hitbox.width > MAP_WIDTH * 64)
            {
                kill(object, i, objects);
                if (is_actually_killed(object))
                {
                    i--;
                    size--;
                }
            }
        }
    }
}

bool is_actually_killed(Object* object)
{
    return (object->type == PARTICLE_NORMAL || object->type == ENEMY_KOOPA || object->type == SIZE_MUSHROOM || object->type == ENEMY_KOOPA_FLYING || object->type == KOOPA_SHELL || object->type == COIN);

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

            if (distance_x(shell, object) < (int)(abs_float(shell->physics.speed.x) + 0.5f) + 10 && object->type != PARTICLE_NORMAL && object->type != SIZE_MUSHROOM)
            {
                if (collide(shell->hitbox, object->hitbox))
                {
                    int dir_x = (shell->physics.speed.x > 0) ? RIGHT : (shell->physics.speed.x < 0 ? LEFT : STATIC);

                    if (dir_x != STATIC)
                    {
                        if (relative_direction(shell, object, dir_x))
                        {
                            if (object->type == ENEMY_KOOPA)
                                spawn_shell(object, list);

                            if (object->type != KOOPA_SHELL && !(object->type == ENEMY_PIRANHA_PLANT && object->animation_frame == 0))
                            {
                                kill(object, i, list);
                                if (is_actually_killed(object))
                                {
                                    i--;
                                    size--;
                                }

                                if (i < shell_index && is_actually_killed(object))
                                {
                                    shell_index--;
                                }
                            }
                            else
                            {
                                object->physics.speed.x = shell->physics.speed.x + (dir_x == RIGHT ? 2.5f : -2.5f);
                            }
                        }
                        // break; <- i guess it can only colide with one object at a time so checking every single one of them is not necessary
                    }
                }
            }
        }
    }
}

void fire_from_cannon(Object* cannon, ObjectsList* list)
{
    if (cannon->counter == 0)
    {
        Object new_bullet;
        bind_bitmap(&new_bullet, cannon->bitmap);

        Physics bullet_physics = create_physics(cannon->type == CANNON_LEFT ? -5.0f : 5.0f, 0.0f, 0.0f, 0.0f, 0.0f);

        if (cannon->type == CANNON_LEFT)
            init_object(&new_bullet, BULLET, cannon->pos_x - (64 - 16), cannon->pos_y, 64, 64, RECTANGLE, cannon->pos_x - (64 - 16), cannon->pos_y + 11, 48, 42, bullet_physics, 1);
        else
            init_object(&new_bullet, BULLET, cannon->pos_x + 64, cannon->pos_y, 64, 64, RECTANGLE, cannon->pos_x + 64 + 16, cannon->pos_y + 11, 48, 42, bullet_physics, 1);

        new_bullet.animation_frame = cannon->type == CANNON_LEFT ? 3 : 2;
        push_back_ol(list, new_bullet);

        cannon->counter = BULLET_FREQUENCY;
    }
    else
        cannon->counter--;
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

void spawn_koopa(Object* enemy, ObjectsList* list)
{
    Object new_koopa = *enemy;
    Physics koopa_physics = create_physics(-3.0f, 0.0f, 3.0f, 20.0f, 2.0f);
    new_koopa.physics = koopa_physics;
    new_koopa.type = ENEMY_KOOPA;

    if (enemy->animation_frame > 6)
        new_koopa.animation_frame = 2;
    else
        new_koopa.animation_frame = 0;

    new_koopa.counter = 46;

    push_back_ol(list, new_koopa);
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

    Object mushroom;

    bind_bitmap(&mushroom, block->bitmap);
    Physics mushroom_physics = create_physics(4.0f, BUMP_AMOUNT, 4.0f, 0.0f, 1.25f);
    init_object(&mushroom, SIZE_MUSHROOM, block->pos_x, block->pos_y - block->height, block->width, block->height, RECTANGLE, block->pos_x, block->pos_y - block->height, block->width, block->height, mushroom_physics, 1);
    mushroom.animation_frame = 4;
    push_back_ol(list, mushroom);

    block->animation_frame = 2;
    block->frames_number = 1;
    block->type = UNBREAKABLE_BLOCK;
}

void spawn_coin(Object* block, ObjectsList* list)
{
    bump_block(block, list);

    //TODO play sound

    // ATTENTION
    //
    // This is probably the dirtiest hack i've ever done: Number of coins in a block is stored in it's
    // mass because it's not used for static objects
    //
    // ATTENTION

    if (block->physics.mass > 0.0f)
    {
        coins++;
        block->physics.mass -= 1.0f;
        Object coin;
        bind_bitmap(&coin, block->bitmap);
        Physics coin_physics = create_physics(0.0f, -18.0f, 0.0f, 0.0f, 2.0f);
        init_object(&coin, PARTICLE_NORMAL, block->pos_x, block->pos_y - block->height, block->width, block->height, RECTANGLE, 0, 0, 1, 1, coin_physics, 1);
        coin.animation_frame = 3;
        coin.counter = 18;
        coin.alive = false;
        push_back_ol(list, coin);
    }

    if (block->physics.mass <= 0.0f)
    {
        block->animation_frame = 2;
        block->frames_number = 1;
        block->type = UNBREAKABLE_BLOCK;
    }
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

    int size = list->size;

    for (int i = 0; i < size; i++)
    {
        Object* temp_obj = get_element_pointer_ol(list, i);

        if (collide(temp_hitbox, temp_obj->hitbox) && temp_obj->type != PARTICLE_NORMAL && temp_obj->type != SIZE_MUSHROOM)
        {
            kill(temp_obj, i, list);

            if (is_actually_killed(temp_obj))
            {
                i--;
                size--;
            }
        }
        else if (temp_obj->type == SIZE_MUSHROOM && collide(temp_hitbox, temp_obj->hitbox)) // making the mushroom go opposite direction
        {
            temp_obj->physics.speed.y += 2.5f * BUMP_AMOUNT;
            temp_obj->physics.speed.x *= -1;
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
