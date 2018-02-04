#include "object_updates.h"
#include "bitmap.h"

#include <string.h>
#include <time.h>

#ifndef _LEVEL
#define _LEVEL

typedef struct LevelList
{
    char path[256];             // level file path
    struct LevelList* previous; // previous element
    struct LevelList* next;     // next element
} LevelList;

// creating new level list from level_index file
LevelList* init_level_list();

// creates a new list element
LevelList* create_list_element(char path[], LevelList* previous);

// frees the memory taken by the list
void delete_level_list(LevelList* list);

// loading a level from a given .lvl file to given data structures
void load_level(char* path, Object level[MAP_HEIGHT][MAP_WIDTH], Object background_elements[MAP_HEIGHT][MAP_WIDTH], ObjectsList* non_static_objects, ObjectsList* clouds);

// adds loaded info to the map array
void parse_map_line(Object level[MAP_HEIGHT][MAP_WIDTH], int line_number, char* line_str);

// adds loaded info to the background array
void parse_background_line(Object background_elements[MAP_HEIGHT][MAP_WIDTH], int line_number, char* line_str);

// adds loaded object to the objects list
void parse_object_line(ObjectsList* list, char* line);

// randomizes clouds in the background
void generate_clouds(ObjectsList* clouds);

// saves the level to the file
void save_level(LevelList* current_level, Object level[MAP_HEIGHT][MAP_WIDTH], Object background[MAP_HEIGHT][MAP_WIDTH], ObjectsList* non_static_elements);

#endif
