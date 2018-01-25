#ifndef _LIST
#define _LIST

#include <stdlib.h>
#include "object.h"

typedef struct
{
    /*
    Dynamic cyclic list of the Object structures
     */

    Object* objects;        // array of objects
    unsigned int size;      // number of elements in the list
    unsigned int capacity;  // maximum capacity of the array
    unsigned int first;     // index of the first element in the list

} ObjectsList;

// creating new list with given initial capacity
ObjectsList create_objects_list(unsigned int initial_capacity);

// returning the i-th element in the list
Object get_element_ol(ObjectsList* list, int i);

// returning the pointer to i-th element in the list
Object* get_element_pointer_ol(ObjectsList* list, int i);

// return the first element and remove it from the list
Object pop_first_ol(ObjectsList* list);

// return the last element and remove it from the list
Object pop_last_ol(ObjectsList* list);

// remove the i-th element of the list and return it
Object pop_element_ol(ObjectsList* list, int i);

// set the i-th element of the list to the given object
void set_element_ol(ObjectsList* list, int i, Object obj);

// add the given object as the last element of the list
void push_back_ol(ObjectsList* list, Object obj);

// remove i-th element from the list (DO NOT USE IT)
void remove_element_ol(ObjectsList* list, int i);

// free the memory taken by the list
void delete_list(ObjectsList* list);

#endif
