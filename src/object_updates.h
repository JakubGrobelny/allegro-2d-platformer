#include "list.h"
#include "util.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef _OBJECT_UPDATES
#define _OBJECT_UPDATES

// // checking if any object collides with given object in given direction
// bool collides_in_direction(Object* object, Object level[], int direction);

// applying the vectors to an object
void apply_vectors(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH]);

// checking whether the object is standing on some platform
bool on_the_ground(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH]);

// making things fall
void apply_gravity(Object* object);

// fix overlaps
void handle_being_stuck(Object* object, Object level[MAP_HEIGHT][MAP_WIDTH], int previous_pos_x, int previous_pos_y);

// updating non-static objects
void update_non_static_objects(ObjectsList* objects, Object level[MAP_HEIGHT][MAP_WIDTH]);

// updating non-static objects' animations
void animate_non_static_objects(ObjectsList* objects, int frame);

// kills an object :( (literally)
void kill(Object* object, int i, ObjectsList* list);

// spawns a shell after a kooppa enemy die
void spawn_shell(Object* enemy, ObjectsList* list);

// goes through the objects list to check whether the shell has collided with something and handles the collision
void check_for_shell_collisions(int shell_index, ObjectsList* list);

#endif
