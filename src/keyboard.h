#ifndef _KEYBOARD_ENUM
#define _KEYBOARD_ENUM

#include <allegro5/allegro.h>
#include <stdbool.h>

typedef enum
{
    /*
    enum with keyboard's keys identifiers
     */

    KEY_DOWN,
    KEY_UP,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ENTER,
    KEY_SPACE,
    KEY_SHIFT,
    KEY_CTRL,

    KEYS_AMOUNT // the amount of the keys specified in this enum

} Keys;

// set all buttons to not pressed/released
void reset_buttons(bool* down, bool* up, unsigned int size);

// check if the status of any button has changed
void update_buttons(ALLEGRO_EVENT* event, bool* keys_down, bool* keys_up, bool* keys_active);

#endif
