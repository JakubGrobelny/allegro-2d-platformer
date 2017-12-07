#include "object.h"

Object create_object(int pos_x, int pos_y, int width, int height, Physics physics, int type)
{
    Object new;
    new.pos_x = pos_x;
    new.pos_y = pos_y;
    new.height = height;
    new.width = width;
    new.physics = physics;
    new.hitbox = create_hitbox(type, pos_x, pos_y, width, height);
    new.sprite = create_sprite(pos_x, pos_y, width, height);
    new.type = type;

    return new;
}

void draw_object(Object* object)
{
    draw_sprite(&(object->sprite), object->type);
}

void update_player(Object* player, bool* key)
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
