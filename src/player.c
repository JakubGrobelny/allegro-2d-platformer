#include "player.h"

ALLEGRO_BITMAP* player_bitmap = NULL;
ALLEGRO_BITMAP* player_big_bitmap = NULL;

void update_player(Object* player, bool* keys_active, bool* keys_down, bool* keys_up, Object level[MAP_HEIGHT][MAP_WIDTH], ObjectsList* non_static, int frame, int* level_status)
{
    Vector previous_speed = player->physics.speed;

    if (player->hitbox.pos_y >= DISPLAY_HEIGHT && player->alive)
        die(player);
    if (player->pos_x + player->width >= END_LINE)
    {
        //TODO: win
        *level_status = 2;
    }

    bool running = false;

    if (player->counter > 0)
        player->counter--;

    if (!player->alive && player->counter == 0)
    {
        if (lives > 0)
        {
            terminate_velocity(player);
            respawn_player(player, START_X, START_Y);
            player->alive = true;
            *level_status = 1;
        }
        else
        {
            player->counter = 200;
            *level_status = 3;
        }
    }

    if (coins == 100)
    {
        coins = 0;
        lives++;
    }

    if (player->alive)
    {
        if ((keys_active[KEY_DOWN] || keys_active[KEY_CTRL]) && player->type == PLAYER_BIG) // TODO: or KEY_LCTRL
        {
            crouch(player);

            if (player->hitbox.height == 128)
            {
                player->hitbox.height -= 38;
                player->hitbox.pos_y += 38;
            }
        }
        else
        {
            if (player->type == PLAYER_BIG)
            {
                if (player->hitbox.height < 128)
                {
                    player->hitbox.height = 128;
                    player->hitbox.pos_y -= 38;
                }
            }

            if (keys_active[KEY_RIGHT])
            {
                player->physics.speed.x += player->physics.acceleration.x;
                running = true;

                if (keys_active[KEY_SHIFT] && on_the_ground(player, level) && player->physics.speed.x >= 0.0f)
                player->physics.speed.x += player->physics.acceleration.x;

                if (player->physics.speed.x > MAX_SPEED)
                player->physics.speed.x = MAX_SPEED;

            }
            if (keys_active[KEY_LEFT])
            {
                player->physics.speed.x -= player->physics.acceleration.x;
                running = true;

                if (keys_active[KEY_SHIFT] && on_the_ground(player, level) && player->physics.speed.x <= 0.0f)
                player->physics.speed.x -= player->physics.acceleration.x;

                if (abs_float(player->physics.speed.x) > MAX_SPEED)
                player->physics.speed.x = -MAX_SPEED;
            }

            if (keys_down[KEY_UP] || keys_down[KEY_SPACE]) // TODO: if active && ~pressed then lower the gravity
            {
                if (can_jump(player, level)) // on_the_ground
                {
                    jump(player);
                }
            }
        }
    }

    if (player->alive && !(keys_active[KEY_DOWN] && !(keys_active[KEY_CTRL]) && player->type == PLAYER_BIG))
        animate_player(player, level, running, frame);

    // temporary friction simulation:
    if (frame % 3 == 0)
    {
        if (player->animation_frame < 14)
            player->physics.speed.x /= 1.11f;
        else
            player->physics.speed.x /= 1.02f;

        if (abs_float(player->physics.speed.x) < 1)
        player->physics.speed.x = 0;
    }

    apply_vectors(player, level, non_static);

    if (player->alive)
        non_static_object_interactions(player, non_static);
}

bool can_jump(Object* player, Object level[MAP_HEIGHT][MAP_WIDTH])
{
    if (on_the_ground(player, level))
        return true;

    const int error = 3;

    int x1, x2;
    int y;

    x1 = player->hitbox.pos_x / 64;
    x2 = (player->hitbox.pos_x + player->hitbox.width) / 64;

    y = (player->hitbox.pos_y + player->hitbox.height + error) / 64;

    if (x1 < 0 || x1 >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT || x2 < 0 || x2 >= MAP_WIDTH)
            return false;

    return (player->physics.speed.y >= 0.0f && (level[y][x1].type != EMPTY || level[y][x2].type != EMPTY));
}

void jump(Object* player)
{
    //if (player->physics.speed.y == 0)
    player->physics.speed.y -= player->physics.acceleration.y;
}

void crouch(Object* player)
{
    if (player->physics.speed.x == 0.0f)
    {
        if (player->animation_frame == 0)
            player->animation_frame = 14;
        else
            player->animation_frame = 15;
    }
    else if (player->physics.speed.x > 0.0f)
        player->animation_frame = 15;
    else
        player->animation_frame = 14;
}

void respawn_player(Object* player, int x, int y)
{
    player->pos_x = x;
    player->pos_y = y;
}

void change_state(Object* player)
{
    // TODO CHANGE SIZE, BITMAP ETC.
    if (player->type == PLAYER)
    {
        player->type = PLAYER_BIG;
        bind_bitmap(player, player_big_bitmap);
        player->height = 128;
        player->hitbox.height = 127;
        player->pos_y -= 64;
        player->hitbox.pos_y -= 64;
        player->physics.mass = 1.0f;
        player->physics.acceleration.x = 0.4f;
    }
    else if (player->type == PLAYER_BIG)
    {
        player->type = PLAYER;
        bind_bitmap(player, player_bitmap);
        player->height = 64;
        player->hitbox.height = 64;
        player->pos_y += 64;
        player->hitbox.pos_y -= 64;
        player->physics.mass = 0.9f;
        player->physics.acceleration.x = 0.47f;
    }
}

void non_static_object_interactions(Object* player, ObjectsList* list)
{
    int size = list->size;
    for (int i = 0; i < size; i++)
    {
        Object* object = get_element_pointer_ol(list, i);

        if (collide(player->hitbox, object->hitbox) && object->type != PARTICLE_NORMAL)
        {
            if (object->type == SIZE_MUSHROOM)
            {
                kill(object, i, list);

                if (is_actually_killed(object))
                {
                    i--;
                    size--;
                }

                if (player->type == PLAYER)
                    change_state(player);
                else
                    lives++;
                continue;
            }

            if (object->type == COIN)
            {
                kill(object, i, list);

                if (is_actually_killed(object))
                {
                    i--;
                    size--;
                }

                coins++;
                continue;
            }

            if (object->type == ENEMY_PIRANHA_PLANT)
            {
                if (object->animation_frame > 1)
                {
                    die(player);
                    player->physics.speed.y = -15.0f;

                    return;
                }
            }

            if (player->physics.speed.y > 0.9f) // && relative_direction(player, object, BOTTOM))
            {
                if (object->type == ENEMY_KOOPA && !object->counter)
                    spawn_shell(object, list);
                else if (object->type == ENEMY_KOOPA_FLYING)
                    spawn_koopa(object, list);

                if (object->type != KOOPA_SHELL && object->type != ENEMY_PIRANHA_PLANT)
                {
                    if (!(object->type == ENEMY_KOOPA && object->counter > 0))
                        kill(object, i, list);
                    if (is_actually_killed(object))
                    {
                        i--;
                        size--;
                    }
                }
                else
                {
                    if (abs_float(object->physics.speed.x) > 0.1f)
                        object->physics.speed.x = 0.0f;
                    else
                    {
                        int player_dir_x = player->physics.speed.x > 0 ? 1 : -1;
                        object->physics.speed.x = player_dir_x * object->physics.acceleration.x;
                    }
                }

                if (object->type != ENEMY_PIRANHA_PLANT)
                    player->physics.speed.y = -15;

            }
            else // touching while going sideways
            {
                if (object->type != KOOPA_SHELL && !(object->type == ENEMY_KOOPA && object->counter > 0))
                {
                    if (!player->counter && !(object->type == ENEMY_PIRANHA_PLANT && object->animation_frame <= 1))
                    {
                        die(player);

                        if (object->type == ENEMY_PIRANHA_PLANT) // at this point i am unable to say if this condition is even possible
                            player->physics.speed.y = - 15.0f;

                        return;
                    }
                    object->physics.speed.x *= -1;
                }
                else
                {
                    if (abs_float(object->physics.speed.x) > 0.1f) // just some inaccuracy to be safe
                    {
                        int dir_x = (object->physics.speed.x > 0) ? RIGHT : (object->physics.speed.x < 0 ? LEFT : STATIC);

                        if (dir_x != STATIC)
                        {
                            if (relative_direction(object, player, dir_x))
                            {
                                if (!player->counter)
                                    die(player);
                                object->physics.speed.x *= -1;
                            }
                            else
                            {
                                object->physics.speed.x = player->physics.speed.x;
                            }
                        }
                    }
                    else if (abs_float(player->physics.speed.x) > 0.1f) // if the shell was stationary
                    {
                        if (relative_direction(player, object, LEFT))
                            object->physics.speed.x = -object->physics.acceleration.x;
                        else if (relative_direction(player, object, RIGHT))
                            object->physics.speed.x = object->physics.acceleration.x;
                    }
                }
            }
        }
    }
}

void animate_player(Object* player, Object level[MAP_HEIGHT][MAP_WIDTH], bool running, int frame)
{
        // jumping
        if (player->physics.speed.y < 0)
        {
            if (player->physics.speed.x < 0)
                player->animation_frame = 5;
            else if (player->physics.speed.x > 0)
                player->animation_frame = 12;
            else
            {
                if (player->animation_frame > 6)
                    player->animation_frame = 12;
                else
                    player->animation_frame = 5;
            }
        }
        // on the ground
        else if (on_the_ground(player, level))
        {
            // idle
            if (player->physics.speed.x == 0 || !running)
            {
                if (player->animation_frame > 6)
                    player->animation_frame = 7;
                else
                    player->animation_frame = 0;
            }
            // running
            else
            {
                // if previously idle
                if (player->animation_frame == 7 || player->animation_frame == 0)
                {
                    // start running to the left/right
                    if (player->physics.speed.x < 0)
                        player->animation_frame = 1;
                    else
                        player->animation_frame = 8;
                }
                // if was running
                else if (running && !(frame % 5) && frame)// && !(frame % ((abs_int((int)(player->physics.speed.x / MAX_SPEED)))))) // frame * player->physics.speed.x / MAX_SPEED
                {
                    if (player->physics.speed.x < 0)
                    {
                        player->animation_frame++;

                        if (player->animation_frame >= 5)
                            player->animation_frame = 2;
                    }
                    else
                    {
                        player->animation_frame++;

                        if (player->animation_frame < 9)
                            player->animation_frame = 9;

                        if (player->animation_frame >= 11)
                            player->animation_frame = 9;
                    }
                }
            }
        }
        // falling
        else
        {
            if (player->physics.speed.x < 0)
                player->animation_frame = 5;
            else if (player->physics.speed.x > 0)
                player->animation_frame = 12;
            else
            {
                if (player->animation_frame > 5)
                    player->animation_frame = 12;
                else
                    player->animation_frame = 5;
            }
        }
}

void die(Object* player)
{
    // TODO: do stuff

    if (player->alive)
    {
        if (player->type == PLAYER_BIG)
        {
            change_state(player);
            player->counter = 50;
            if (player->hitbox.pos_y + 64 > DISPLAY_HEIGHT)
                die(player);
        }
        else
        {
            // actually die and do stuff
            player->alive = false;
            player->animation_frame = 14;
            terminate_velocity(player);
            player->physics.speed.y = -25.0f;
            player->counter = 120;
            lives--;
        }
    }
}
