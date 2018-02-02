#include "object_updates.h"
#include "bitmaps.h"

#ifndef _LEVEL
#define _LEVEL

// loading a level from a given .lvl file to given data structures
void load_level(char* path, Object level[MAP_HEIGHT][MAP_WIDTH], Object background_elements[MAP_HEIGHT][MAP_WIDTH], ObjectsList* non_static_objects, ObjectsList*);

// adds loaded info to the map array
void parse_map_line(Object level[MAP_HEIGHT][MAP_WIDTH], int line_number, char* line_str);

// adds loaded info to the background array
void parse_background_line(Object background_elements[MAP_HEIGHT][MAP_WIDTH], int line_number, char* line_str);

// adds loaded object to the objects list
void parse_object_line(ObjectsList* list, char* line);

#endif
