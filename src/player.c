#include "player.h"

void update_player(Object* player, bool* keys_active, bool* keys_down, bool* keys_up, ObjectsList* list)
{
    if (player->pos_y > DISPLAY_HEIGHT) // just for testings
        respawn_player(player, 250, 250);

    if (on_the_ground(player, list))
            player->physics.speed.y = 0;
    else
        apply_gravity(player);

    if (keys_active[KEY_DOWN]) // TODO: or KEY_LCTRL
    {
        crouch(player);
    }
    if (keys_active[KEY_RIGHT])
    {
        player->physics.speed.x += player->physics.acceleration.x;

        if (player->physics.speed.x > MAX_SPEED)
            player->physics.speed.x = MAX_SPEED;
    }
    if (keys_active[KEY_LEFT])
    {
        player->physics.speed.x -= player->physics.acceleration.x;

        if (abs_float(player->physics.speed.x) > MAX_SPEED)
            player->physics.speed.x = -MAX_SPEED;
    }

    if (keys_down[KEY_UP])
    {
        jump(player);
        player->pos_y--; // an ugly hack but it works so I am not going to change it
    }
    if (keys_down[KEY_ENTER])
    {
        if (player->animation_frame + 1 < player->frames_number)
        {
            player->animation_frame++;
        }
        else
        {
            player->animation_frame = 0;
        }
    }

    // temporary friction simulation:
    player->physics.speed.x /= 1.1f;
    if (abs_float(player->physics.speed.x) < 0.2f)
        player->physics.speed.x = 0;

    apply_vectors(player, list);

    player->hitbox.pos_y = player->pos_y;
    player->hitbox.pos_x = player->pos_x;
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
