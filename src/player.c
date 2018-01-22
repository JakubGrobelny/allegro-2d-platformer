#include "player.h"

void update_player(Object* player, bool* keys_active, bool* keys_down, bool* keys_up, ObjectsList* list, int frame)
{
    Vector previous_speed = player->physics.speed;

    if (player->hitbox.pos_y >= DISPLAY_HEIGHT && player->alive)
        die(player);

    if (on_the_ground(player, list))
            player->physics.speed.y = 0;
    else
        apply_gravity(player);

    bool running = false;

    if (keys_active[KEY_DOWN] && player->alive) // TODO: or KEY_LCTRL
    {
        crouch(player);
    }
    if (keys_active[KEY_RIGHT] && player->alive)
    {
        if (player->physics.speed.y == previous_speed.y) // on_the_ground
        {
            player->physics.speed.x += player->physics.acceleration.x;

            running = true;
        }
        else
        {
            player->physics.speed.x += (player->physics.acceleration.x / 1.25f);
        }

        if (player->physics.speed.x > MAX_SPEED)
            player->physics.speed.x = MAX_SPEED;

    }
    if (keys_active[KEY_LEFT] && player->alive)
    {
        if (player->physics.speed.y == previous_speed.y) // on_the_ground
        {
            player->physics.speed.x -= player->physics.acceleration.x;

            running = true;
        }
        else
        {
            player->physics.speed.x -= (player->physics.acceleration.x / 1.25f);
        }

        if (abs_float(player->physics.speed.x) > MAX_SPEED)
            player->physics.speed.x = -MAX_SPEED;
    }

    if (keys_down[KEY_UP] && player->alive)
    {
        if (player->physics.speed.y == previous_speed.y) // on_the_ground
        {
            jump(player);
            //player->pos_y--;
        }
    }

    if (player->alive)
        animate_player(player, list, running, frame);

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

void die(Object* player)
{
    player->alive = false;
    player->animation_frame = 14;
    terminate_velocity(player);
    // TODO: player->hitbox.collision = false // turn off collisions
    player->physics.speed.y = -19.75f;
    player->physics.mass /= 2.0f; // TODO: cancel it
}
