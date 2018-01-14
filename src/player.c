#include "player.h"

void update_player(Object* player, bool* keys_active, bool* keys_down, bool* keys_up, ObjectsList* list)
{
    if (keys_active[KEY_UP])
    {
        player->pos_y -= 10;
    }
    if (keys_active[KEY_DOWN])
    {
        player->pos_y += 10;
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

    // TODO: Ograniczyc ruch gracza do rozmiarow okna

    player->hitbox.pos_y = player->pos_y;
    player->hitbox.pos_x = player->pos_x;
}
