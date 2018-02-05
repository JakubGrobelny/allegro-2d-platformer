#include "level.h"
#include "string.h"
#include "interface.h"

#ifndef _EDTIOR
#define _EDITOR

extern int selected_object;
extern int selected_layer; // 0 - map, 1 - background, 2 - objects
const int layer_max_object[3];// amount of possible object types on every layer

typedef enum
{
    MAP_LAYER,
    BACKGROUND_LAYER,
    OBJECT_LAYER
} EditorLayers;

// selecting a level to edit
LevelList* select_level(LevelList* level_list, ALLEGRO_EVENT_QUEUE* event_queue, bool* keys_active, bool* keys_down, bool* keys_up);

// calculates the offset in the editor mode
int move_screen(bool* keys_down, bool* keys_up, bool* keys_active);

// adding/removing objects
void update_editor(Object* editor_obj, bool* keys_down, bool* keys_up, bool* keys_active, Object level[MAP_HEIGHT][MAP_WIDTH], Object background[MAP_HEIGHT][MAP_WIDTH], ObjectsList* objects, int screen_offset);

// assings proper texture and position to the temporary object
Object* select_object(Object* editor_obj, int pos_x, int pos_y);

#endif
