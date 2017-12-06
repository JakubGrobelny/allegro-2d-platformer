#include "player.h"

Player create_player(int pos_x, int pos_y, int width, int height)
{
    Player new;
    new.pos_x = pos_x;
    new.pos_y = pos_y;
    new.height = height;
    new.width = width;
    new.hitbox = create_hitbox(rectangle, pos_x, pos_y, width, height);
    new.sprite = create_sprite(pos_x, pos_y, width, height);

    return new;
}

void draw_player(Player* player)
{
    draw_sprite(&(player->sprite));
}
