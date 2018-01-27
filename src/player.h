#include "list.h"
#include "util.h"
#include "object_updates.h"
#include "defines.h"
#include <stdbool.h>
#include <stdio.h>

#ifndef _PLAYER
#define _PLAYER

extern ALLEGRO_BITMAP* player_bitmap;
extern ALLEGRO_BITMAP* player_big_bitmap;

// apply keypresses etc. to the player object
void update_player(Object* player, bool* keys_active, bool* keys_down, bool* keys_up, Object level[MAP_HEIGHT][MAP_WIDTH], ObjectsList* non_static, int frame);

// making the player jump
void jump(Object* player);

// making the player crouch
void crouch(Object* player);

// respawns the player at given position
void respawn_player(Object* player, int x, int y);

// changes player's current sprite
void animate_player(Object* player, Object level[MAP_HEIGHT][MAP_WIDTH], bool running, int frame);

// killing the player
void die(Object* player);

// checking the collisions with non static objects
void non_static_object_interactions(Object* player, ObjectsList* list);

#endif
