#include "list.h"
#include "util.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef _OBJECT_UPDATES
#define _OBJECT_UPDATES

int lives; // extern variables
int coins;

// applying the vectors to an object
void apply_vectors(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH], ObjectsList* list);

// checking whether the object is standing on some platform
bool on_the_ground(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH]);

// making things fall
void apply_gravity(Object* object);

// fix overlaps
void handle_being_stuck(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH], int previous_pos_x, int previous_pos_y);

// updating non-static objects
void update_non_static_objects(ObjectsList* objects, Object level[MAP_HEIGHT][MAP_WIDTH], Object* player);

// updating non-static objects' animations
void animate_non_static_objects(ObjectsList* objects, int frame, Object* player);

// updating static objects' animations
void animate_static_objects(Object level[MAP_HEIGHT][MAP_WIDTH], int frame, Object* player);

// kills an object :( (literally)
void kill(Object* object, int i, ObjectsList* list);

// spawns a shell after a koopa enemy die
void spawn_shell(Object* enemy, ObjectsList* list);

// spawns a koopa enemy when flying one is killed
void spawn_koopa(Object* enemy, ObjectsList* list);

// goes through the objects list to check whether the shell has collided with something and handles the collision
void check_for_shell_collisions(int shell_index, ObjectsList* list);

// add some y velocity to the block that was hit by the player
void bump_block(Object* block, ObjectsList* list);

// spawn mushroom from a secret block
void spawn_mushroom(Object* block, ObjectsList* list);

// spawn coin from a secret block
void spawn_coin(Object* block, ObjectsList* list);

// destroy the block that was hit by big mario
void break_block(Object* block, ObjectsList* list);

// kills enemies that are walking on given block
void kill_enemies_above_block(Object* block, ObjectsList* list);

#endif
