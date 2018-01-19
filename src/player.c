#include "player.h"

void update_player(Object* player, bool* keys_active, bool* keys_down, bool* keys_up, ObjectsList* list, int frame)
{
    //printf("X: %d Y: %d\n", player->hitbox.pos_x, player->hitbox.pos_y);// test

    if (player->pos_y > DISPLAY_HEIGHT) // just for testings
        respawn_player(player, 250, 250);

    //if (on_the_ground(player, list))
    //        player->physics.speed.y = 0;
    //else
    //    apply_gravity(player);

    bool running = false;

    if (keys_active[KEY_DOWN]) // TODO: or KEY_LCTRL
    {
        player->physics.speed.y += player->physics.acceleration.y;
        //crouch(player);
    }
    if (keys_active[KEY_RIGHT])
    {
        //if (on_the_ground(player, list))
        //{
        //    player->physics.speed.x += player->physics.acceleration.x;

        //    running = true;
        //}
        //else
        //{
            player->physics.speed.x += (player->physics.acceleration.x / 1.25f);
        //}

        if (player->physics.speed.x > MAX_SPEED)
            player->physics.speed.x = MAX_SPEED;

    }
    if (keys_active[KEY_LEFT])
    {
        //if (on_the_ground(player, list))
        //{
        //    player->physics.speed.x -= player->physics.acceleration.x;

        //    running = true;
        //}
        //else
        //{
            player->physics.speed.x -= (player->physics.acceleration.x / 1.25f);
        //}

        if (abs_float(player->physics.speed.x) > MAX_SPEED)
            player->physics.speed.x = -MAX_SPEED;
    }

    if (keys_active[KEY_UP])
    {
        player->physics.speed.y -= player->physics.acceleration.y;

        //jump(player);
        //player->pos_y--; // an ugly hack but it works so I am not going to change it
    }

    if (keys_active[KEY_ENTER])
    {
        player->physics.speed.y = 0;
        player->physics.speed.x = 0;
    }

    animate_player(player, list, running, frame);

    /*
    // temporary friction simulation:
    if (on_the_ground(player, list))
    {
        player->physics.speed.x /= 1.1f;
        if (abs_float(player->physics.speed.x) < 0.2f)
            player->physics.speed.x = 0;
    }
    else
    {
        player->physics.speed.x /= 1.05f;
        if (abs_float(player->physics.speed.x) < 0.2f)
            player->physics.speed.x = 0;
    }
    */
    apply_vectors(player, list);

    player->hitbox.pos_y = player->pos_y + (player->height - player->hitbox.height) / 2;
    player->hitbox.pos_x = player->pos_x + (player->width - player->hitbox.width) / 2;
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

void animate_player(Object* player, ObjectsList* list, bool running, int frame)
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
        else if (on_the_ground(player, list))
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
                else if (running && !(frame % 5 / (player->physics.speed.x / MAX_SPEED) )) // frame * player->physics.speed.x / MAX_SPEED
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
