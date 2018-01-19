#include "list.h"
#include "util.h"
#include "object_updates.h"
#include "defines.h"
#include <stdbool.h>
#include <stdio.h>

#ifndef _PLAYER
#define _PLAYER

// apply keypresses etc. to the player object
void update_player(Object* player, bool* keys_active, bool* keys_down, bool* keys_up, ObjectsList* list, int frame);

// making the player jump
void jump(Object* player);

// making the player crouch
void crouch(Object* player);

// respawns the player at given position
void respawn_player(Object* player, int x, int y);

// changes player's current sprite
void animate_player(Object* player, ObjectsList* list, bool running, int frame);

#endif
