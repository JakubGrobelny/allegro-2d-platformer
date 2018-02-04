#ifndef _KEYBOARD_ENUM
#define _KEYBOARD_ENUM

#include <allegro5/allegro.h>
#include <stdbool.h>

typedef enum
{
    /*
    enum with keyboard's keys identifiers
     */

    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,

    KEY_DOWN,
    KEY_UP,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ENTER,
    KEY_SPACE,
    KEY_SHIFT,
    KEY_CTRL,
    KEY_BACKSPACE,
    KEY_RSHIFT,

    KEYS_AMOUNT // the amount of the keys specified in this enum

} Keys;

// set all buttons to not pressed/released
void reset_buttons(bool* down, bool* up, unsigned int size);

// check if the status of any button has changed
void update_buttons(ALLEGRO_EVENT* event, bool* keys_down, bool* keys_up, bool* keys_active);

#endif
