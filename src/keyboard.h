#ifndef _KEYBOARD_ENUM
#define _KEYBOARD_ENUM

#include <allegro5/allegro.h>
#include <stdbool.h>

typedef enum
{
    KEY_DOWN,
    KEY_UP,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ENTER,

    KEYS_AMOUNT
} Keys;

void reset_buttons(bool* down, bool* up, unsigned int size);
void update_buttons(ALLEGRO_EVENT* event, bool* keys_down, bool* keys_up, bool* keys_active);

#endif
