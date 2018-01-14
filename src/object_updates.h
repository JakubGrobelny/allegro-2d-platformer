#include "list.h"

#ifndef _OBJECT_UPDATES
#define _OBJECT_UPDATES

// checking if given object collides with any other object in the given direction
bool collides_in_direction(Object* object, ObjectsList* list, int direction);

// applying the vectors to an object
void apply_vectors(Object* object, ObjectsList* list);

#endif
