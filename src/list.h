#ifndef _LIST
#define _LIST

#include "object.h"
#include <stdlib.h>

typedef struct
{
    Object* objects;
    unsigned int size;
    unsigned int capacity;
    unsigned int first;

} ObjectsList;

ObjectsList create_objects_list(unsigned int initial_capacity);
Object get_element_ol(ObjectsList* list, int i);
Object pop_first_ol(ObjectsList* list);
Object pop_last_ol(ObjectsList* list);
Object pop_element_ol(ObjectsList* list, int i);
void set_element_ol(ObjectsList* list, int i, Object obj);
void push_back_ol(ObjectsList* list, Object obj);
void remove_element_ol(ObjectsList* list, int i);
void delete_list(ObjectsList* list);
#endif
