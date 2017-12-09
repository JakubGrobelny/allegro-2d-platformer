#include "player.h"

void update_player(Object* player, bool* keys_active, bool* keys_down, bool* keys_up, ObjectsList* list)
{
    if (keys_active[KEY_UP])
    {
        player->pos_y -= 10; // hardcoded poki co
    }
    if (keys_active[KEY_DOWN])
    {
        player->pos_y += 10;
    }
    if (keys_active[KEY_RIGHT])
    {
        player->pos_x += 10;
    }
    if (keys_active[KEY_LEFT])
    {
        player->pos_x -= 10;
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
