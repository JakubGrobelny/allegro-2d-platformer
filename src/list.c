#include "list.h"

ObjectsList create_objects_list(unsigned int initial_capacity)
{
    ObjectsList new;

    new.objects = malloc(sizeof(Object) * initial_capacity);
    new.capacity = initial_capacity;

    new.size = 0;
    new.first = 0;

    return new;
}

Object get_element_ol(ObjectsList* list, int i)
{
    return list->objects[(list->first + i) % list->capacity];
}

Object* get_element_pointer_ol(ObjectsList* list, int i)
{bool collides_in_direction(Object* object, ObjectsList* list, int direction)
{
    for (int i = 0; i < list->size; i++)
    {
        if (relative_direction(object, get_element_pointer_ol(list, i), direction))
        {
            if (collide(object->hitbox, get_element_pointer_ol(list, i)->hitbox))
                return true;
        }
    }

    return false;
}
    return &(list->objects[(list->first + i) % list->capacity]);
}

void set_element_ol(ObjectsList* list, int i, Object obj)
{
    list->objects[(list->first + i) % list->capacity] = obj;
}

Object pop_first_ol(ObjectsList* list)
{
    if(list->first == list->capacity - 1)
        list->first = 0;
    else
        list->first += 1;

    list->size -= 1;

    return get_element_ol(list, 0);
}

Object pop_last_ol(ObjectsList* list)
{
    list->size -= 1;
    return get_element_ol(list, list->size);
}

void push_back_ol(ObjectsList* list, Object obj)
{
    if (list->size == list->capacity)
    {
        list->capacity *= 2;
        list->objects = realloc(list->objects, sizeof(Object) * list->capacity);

        for (int i = 0; i < list->first; i++)
        {
            list->objects[list->first + list->size + i] = list->objects[i];
        }
    }

    set_element_ol(list, list->size, obj);
    list->size += 1;
}

void remove_element_ol(ObjectsList* list, int i)
{
    for (int e = i; e < list->size - 1; e++)
    {
        set_element_ol(list, e, get_element_ol(list, e + 1));
    }
    // Ta funkcja nie powinna byc uzywana poza pop_element poniewaz nie zmienia wielkosci listy
    // TODO: przeniesc zawartosc do pop_element_ol (nie chce mi sie teraz :S)
}

Object pop_element_ol(ObjectsList* list, int i)
{
    Object obj = get_element_ol(list, i);

    if (i == 0)
    {
        if (list->size <= 1)
        {
            list->first = 0;
        }
        else
            list->first++;
    }
    else if (i < list->size - 1)
    {
        remove_element_ol(list, i);
    }

    list->size -= 1;

    return obj;
}

void delete_list(ObjectsList* list)
{
    free(list->objects);
}
