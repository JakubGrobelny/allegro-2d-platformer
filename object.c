#include "object.h"

Object create_object(int pos_x, int pos_y, int width, int height, int vel_vertical, int vel_horizontal)
{
    Object new;
    new.pos_x = pos_x;
    new.pos_y = pos_y;
    new.height = height;
    new.width = width;
    new.speed_vertical = vel_vertical;
    new.speed_horizontal = vel_horizontal;
    new.hitbox = create_hitbox(rectangle, pos_x, pos_y, width, height);
    new.sprite = create_sprite(pos_x, pos_y, width, height);

    return new;
}

void draw_object(Object* object)
{
    draw_sprite(&(object->sprite));
}

void update_player(Object* player, bool* key)
{
    if (key[KEY_UP])
    {
        player->pos_y -= player->speed_vertical;
    }
    if (key[KEY_DOWN])
    {
        player->pos_y += player->speed_vertical;
    }
    if (key[KEY_RIGHT])
    {
        player->pos_x += player->speed_horizontal;
    }
    if (key[KEY_LEFT])
    {
        player->pos_x -= player->speed_horizontal;
    }

    // TODO: Ograniczyc ruch gracza do rozmiarow okna

    player->sprite.pos_y = player->pos_y;
    player->sprite.pos_x = player->pos_x;
    player->hitbox.pos_y = player->pos_y;
    player->hitbox.pos_x = player->pos_x;
}
