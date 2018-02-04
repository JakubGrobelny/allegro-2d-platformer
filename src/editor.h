#include "level.h"
#include "string.h"
#include "interface.h"

#ifndef _EDTIOR
#define _EDITOR

// selecting a level to edit
LevelList* select_level(LevelList* level_list, ALLEGRO_EVENT_QUEUE* event_queue, bool* keys_active, bool* keys_down, bool* keys_up);

#endif
