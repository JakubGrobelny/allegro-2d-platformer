#include "list.h"
#include "util.h"
#include "object_updates.h"

#ifndef _PLAYER
#define _PLAYER

// apply keypresses etc. to the player object
void update_player(Object* player, bool* keys_active, bool* keys_down, bool* keys_up, ObjectsList* list);

// making the player jump
void jump(Object* player);

// making the player crouch
void crouch(Object* player);

#endif
