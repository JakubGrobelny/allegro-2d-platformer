#include "player.h"

Player create_player(int pos_x, int pos_y, int width, int height, int velocity)
{
    Player new;
    new.pos_x = pos_x;
    new.pos_y = pos_y;
    new.height = height;
    new.width = width;
    new.velocity = velocity;
    new.hitbox = create_hitbox(rectangle, pos_x, pos_y, width, height);
    new.sprite = create_sprite(pos_x, pos_y, width, height);

    return new;
}

void draw_player(Player* player)
{
    draw_sprite(&(player->sprite));
}

void update_player(Player* player, bool* key)
{
    if (key[KEY_UP])
    {
        player->pos_y -= player->velocity;
    }
    if (key[KEY_DOWN])
    {
        player->pos_y += player->velocity;
    }
    if (key[KEY_RIGHT])
    {
        player->pos_x += player->velocity;
    }
    if (key[KEY_LEFT])
    {
        player->pos_x -= player->velocity;
    }

    player->sprite.pos_y = player->pos_y;
    player->sprite.pos_x = player->pos_x;
    player->hitbox.pos_y = player->pos_y;
    player->hitbox.pos_x = player->pos_x;
}
