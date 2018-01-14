#include "list.h"

#ifndef _OBJECT_UPDATES
#define _OBJECT_UPDATES

// checking if given object collides with any other object in the given direction
bool collides_in_direction(Object* object, ObjectsList* list, int direction);

// applying the vectors to an object
void apply_vectors(Object* object, ObjectsList* list);

// checking whether the object is standing on some platform
bool on_the_ground(Object* object, ObjectsList* list);

// making things fall
void apply_gravity(Object* object);

#endif
