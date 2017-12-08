#include "player.h"

void update_player(Object* player, bool* key, ObjectsList* list)
{
    if (key[KEY_UP])
    {
        player->pos_y -= 10; // hardcoded poki co
    }
    if (key[KEY_DOWN])
    {
        player->pos_y += 10;
    }
    if (key[KEY_RIGHT])
    {
        player->pos_x += 10;
    }
    if (key[KEY_LEFT])
    {
        player->pos_x -= 10;
    }

    // TODO: Ograniczyc ruch gracza do rozmiarow okna

    player->sprite.pos_y = player->pos_y;
    player->sprite.pos_x = player->pos_x;
    player->hitbox.pos_y = player->pos_y;
    player->hitbox.pos_x = player->pos_x;
}
