#include "list.h"
#include "util.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef _OBJECT_UPDATES
#define _OBJECT_UPDATES

// checking if any object collides with given object in given direction
bool collides_in_direction(Object* object, ObjectsList* list, int direction);

// applying the vectors to an object
void apply_vectors(Object* object, ObjectsList* list);

// checking whether the object is standing on some platform
bool on_the_ground(Object* object, ObjectsList* list);

// making things fall
void apply_gravity(Object* object);

// updating non-static objects
void update_non_static_objects(ObjectsList* non_static_objects, ObjectsList* static_objects);

// kills an object :( (literally)
void kill(Object* object);

#endif
