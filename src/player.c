#include "player.h"

void update_player(Object* player, bool* keys_active, bool* keys_down, bool* keys_up, ObjectsList* list)
{
    if (keys_active[KEY_UP])
    {
        jump(player);
    }
    if (keys_active[KEY_DOWN])
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

    apply_gravity(player);
    apply_vectors(player, list);

    // TODO: Ograniczyc ruch gracza do rozmiarow okna

    player->hitbox.pos_y = player->pos_y;
    player->hitbox.pos_x = player->pos_x;
}

void jump(Object* player)
{
    // TODO:
    // 1. check whether the player is on the ground
    // 2. jump

    player->physics.speed.y = 0; // will be changed when on_the_ground() is implemented

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
