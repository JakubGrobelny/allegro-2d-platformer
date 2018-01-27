#include "player.h"

void update_player(Object* player, bool* keys_active, bool* keys_down, bool* keys_up, Object level[MAP_HEIGHT][MAP_WIDTH], ObjectsList* non_static, int frame)
{
    Vector previous_speed = player->physics.speed;

    if (player->hitbox.pos_y >= DISPLAY_HEIGHT && player->alive)
        die(player);

    bool running = false;

    if (player->alive)
    {
        if (keys_active[KEY_DOWN]) // TODO: or KEY_LCTRL
        {
            crouch(player);
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
            if (player->physics.speed.y == previous_speed.y) // on_the_ground
            {
                jump(player);
            }
        }
    }

    if (player->alive)
        animate_player(player, level, running, frame);

    // temporary friction simulation:
    if (frame % 3 == 0)
    {
        player->physics.speed.x = (int)(player->physics.speed.x / 1.02f);
        if (abs_float(player->physics.speed.x) < 1)
        player->physics.speed.x = 0;
    }

    apply_vectors(player, level, non_static);

    if (player->alive)
        non_static_object_interactions(player, non_static);
}

void jump(Object* player)
{
    if (player->physics.speed.y == 0)
        player->physics.speed.y -= player->physics.acceleration.y;
}

void crouch(Object* player)
{
    // TODO:
    // 1. check if mario is big
    // 2. change height and sprite
    // 3. ???
    // 4. profit
}

void respawn_player(Object* player, int x, int y)
{
    player->pos_x = x;
    player->pos_y = y;

    player->physics.speed.x = 0;
    player->physics.speed.x = 0;
}

void change_state(Object* player)
{
    // TODO CHANGE SIZE, BITMAP ETC.
    if (player->type == PLAYER)
    {
        player->type = PLAYER_BIG;

    }
    else if (player->type == PLAYER_BIG)
    {
        player->type = PLAYER;

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
                size--;

                // TODO growth animation
                //
                if (player->type == PLAYER)
                    change_state(player);
                else
                    lives++;
                continue;
            }

            if (player->physics.speed.y > 0 && relative_direction(player, object, BOTTOM))
            {
                if (object->type == ENEMY_KOOPA)
                    spawn_shell(object, list);

                if (object->type != KOOPA_SHELL)
                {
                    kill(object, i, list);
                    size--;
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

                player->physics.speed.y = -15;

            }
            else
            {

                if (object->type != KOOPA_SHELL)
                    die(player);
                else
                {
                    if (abs_float(object->physics.speed.x) > 1.0f) // just some inaccuracy to be safe
                    {
                        int dir_x = (object->physics.speed.x > 0) ? RIGHT : (object->physics.speed.x < 0 ? LEFT : STATIC);

                        if (dir_x != STATIC)
                        {
                            if (relative_direction(object, player, dir_x))
                                die(player);
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
            {
                player->animation_frame = 5;
            }
            else if (player->physics.speed.x > 0)
            {
                player->animation_frame = 12;
            }
            else
            {
                if (player->animation_frame > 6)
                {
                    player->animation_frame = 12;
                }
                else
                {
                    player->animation_frame = 5;
                }
            }
        }
        // on the ground
        else if (on_the_ground(player, level))
        {
            // idle
            if (player->physics.speed.x == 0 || !running)
            {
                if (player->animation_frame > 6)
                {
                    player->animation_frame = 7;
                }
                else
                {
                    player->animation_frame = 0;
                }
            }
            // running
            else
            {
                // if previously idle
                if (player->animation_frame == 7 || player->animation_frame == 0)
                {
                    // start running to the left/right
                    if (player->physics.speed.x < 0)
                    {
                        player->animation_frame = 1;
                    }
                    else
                    {
                        player->animation_frame = 8;
                    }
                }
                // if was running
                else if (running && !(frame % 5) && frame)// && !(frame % ((abs_int((int)(player->physics.speed.x / MAX_SPEED)))))) // frame * player->physics.speed.x / MAX_SPEED
                {
                    if (player->physics.speed.x < 0)
                    {
                        player->animation_frame++;

                        if (player->animation_frame >= 4)
                        {
                            player->animation_frame = 1;
                        }
                    }
                    else
                    {
                        player->animation_frame++;

                        if (player->animation_frame < 9)
                        {
                            player->animation_frame = 9;
                        }

                        if (player->animation_frame >= 11)
                        {
                            player->animation_frame = 9;
                        }
                    }
                }
            }
        }
        // falling
        else
        {
            if (player->physics.speed.x < 0)
            {
                player->animation_frame = 6;
            }
            else if (player->physics.speed.x > 0)
            {
                player->animation_frame = 13;
            }
            else
            {
                if (player->animation_frame > 6)
                {
                    player->animation_frame = 13;
                }
                else
                {
                    player->animation_frame = 6;
                }
            }
        }
}

void die(Object* player)
{
    // TODO: check player's size and do stuff

    if (player->alive)
    {
        player->alive = false;
        player->animation_frame = 14;
        terminate_velocity(player);
        player->physics.speed.y = -25.0f;
    }
}
