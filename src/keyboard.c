#include "keyboard.h"

void reset_buttons(bool* down, bool* up, unsigned int size)
{
    for (int i = 0; i < size; i++)
    {
        down[i] = false;
        up[i] = false;
    }
}

void update_buttons(ALLEGRO_EVENT* event, bool* keys_down, bool* keys_up, bool* keys_active)
{
    if(event->type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(event->keyboard.keycode)
        {
            case ALLEGRO_KEY_UP:
                keys_active[KEY_UP] = true;
                keys_down[KEY_UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys_active[KEY_DOWN] = true;
                keys_down[KEY_DOWN] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys_active[KEY_LEFT] = true;
                keys_down[KEY_LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys_active[KEY_RIGHT] = true;
                keys_down[KEY_RIGHT] = true;
                break;
            case ALLEGRO_KEY_ENTER:
                keys_active[KEY_ENTER] = true;
                keys_down[KEY_ENTER] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys_active[KEY_SPACE] = true;
                keys_down[KEY_SPACE] = true;
                break;
            case ALLEGRO_KEY_LSHIFT:
                keys_active[KEY_SHIFT] = true;
                keys_down[KEY_SHIFT] = true;
                break;
            case ALLEGRO_KEY_LCTRL:
                keys_active[KEY_CTRL] = true;
                keys_down[KEY_CTRL] = true;
                break;
            case ALLEGRO_KEY_Q:
                keys_active[KEY_Q] = true;
                keys_down[KEY_Q] = true;
                break;
            case ALLEGRO_KEY_W:
                keys_active[KEY_W] = true;
                keys_down[KEY_W] = true;
                break;
            case ALLEGRO_KEY_E:
                keys_active[KEY_E] = true;
                keys_down[KEY_E] = true;
                break;
            case ALLEGRO_KEY_R:
                keys_active[KEY_R] = true;
                keys_down[KEY_R] = true;
                break;
            case ALLEGRO_KEY_T:
                keys_active[KEY_T] = true;
                keys_down[KEY_T] = true;
                break;
            case ALLEGRO_KEY_Y:
                keys_active[KEY_Y] = true;
                keys_down[KEY_Y] = true;
                break;
            case ALLEGRO_KEY_U:
                keys_active[KEY_U] = true;
                keys_down[KEY_U] = true;
                break;
            case ALLEGRO_KEY_I:
                keys_active[KEY_I] = true;
                keys_down[KEY_I] = true;
                break;
            case ALLEGRO_KEY_O:
                keys_active[KEY_O] = true;
                keys_down[KEY_O] = true;
                break;
            case ALLEGRO_KEY_P:
                keys_active[KEY_P] = true;
                keys_down[KEY_P] = true;
                break;
            case ALLEGRO_KEY_A:
                keys_active[KEY_A] = true;
                keys_down[KEY_A] = true;
                break;
            case ALLEGRO_KEY_S:
                keys_active[KEY_S] = true;
                keys_down[KEY_S] = true;
                break;
            case ALLEGRO_KEY_D:
                keys_active[KEY_D] = true;
                keys_down[KEY_D] = true;
                break;
            case ALLEGRO_KEY_F:
                keys_active[KEY_F] = true;
                keys_down[KEY_F] = true;
                break;
            case ALLEGRO_KEY_G:
                keys_active[KEY_G] = true;
                keys_down[KEY_G] = true;
                break;
            case ALLEGRO_KEY_H:
                keys_active[KEY_H] = true;
                keys_down[KEY_H] = true;
                break;
            case ALLEGRO_KEY_J:
                keys_active[KEY_J] = true;
                keys_down[KEY_J] = true;
                break;
            case ALLEGRO_KEY_K:
                keys_active[KEY_K] = true;
                keys_down[KEY_K] = true;
                break;
            case ALLEGRO_KEY_L:
                keys_active[KEY_L] = true;
                keys_down[KEY_L] = true;
                break;
            case ALLEGRO_KEY_Z:
                keys_active[KEY_Z] = true;
                keys_down[KEY_Z] = true;
                break;
            case ALLEGRO_KEY_X:
                keys_active[KEY_X] = true;
                keys_down[KEY_X] = true;
                break;
            case ALLEGRO_KEY_C:
                keys_active[KEY_C] = true;
                keys_down[KEY_C] = true;
                break;
            case ALLEGRO_KEY_V:
                keys_active[KEY_V] = true;
                keys_down[KEY_V] = true;
                break;
            case ALLEGRO_KEY_B:
                keys_active[KEY_B] = true;
                keys_down[KEY_B] = true;
                break;
            case ALLEGRO_KEY_N:
                keys_active[KEY_N] = true;
                keys_down[KEY_N] = true;
                break;
            case ALLEGRO_KEY_M:
                keys_active[KEY_M] = true;
                keys_down[KEY_M] = true;
                break;
            case ALLEGRO_KEY_BACKSPACE:
                keys_active[KEY_BACKSPACE] = true;
                keys_down[KEY_BACKSPACE] = true;
                break;
            case ALLEGRO_KEY_RSHIFT:
                keys_active[KEY_RSHIFT] = true;
                keys_down[KEY_RSHIFT] = true;
                break;
        }
    }
    else if (event->type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(event->keyboard.keycode)
        {
            case ALLEGRO_KEY_UP:
                keys_active[KEY_UP] = false;
                keys_up[KEY_UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys_active[KEY_DOWN] = false;
                keys_up[KEY_DOWN] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys_active[KEY_LEFT] = false;
                keys_up[KEY_LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys_active[KEY_RIGHT] = false;
                keys_up[KEY_RIGHT] = true;
                break;
            case ALLEGRO_KEY_ENTER:
                keys_active[KEY_ENTER] = false;
                keys_up[KEY_ENTER] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys_active[KEY_SPACE] = false;
                keys_up[KEY_SPACE] = true;
                break;
            case ALLEGRO_KEY_LSHIFT:
                keys_active[KEY_SHIFT] = false;
                keys_up[KEY_SHIFT] = true;
                break;
            case ALLEGRO_KEY_LCTRL:
                keys_active[KEY_CTRL] = false;
                keys_up[KEY_CTRL] = true;
                break;
            case ALLEGRO_KEY_Q:
                keys_active[KEY_Q] = false;
                keys_up[KEY_Q] = true;
                break;
            case ALLEGRO_KEY_W:
                keys_active[KEY_W] = false;
                keys_up[KEY_W] = true;
                break;
            case ALLEGRO_KEY_E:
                keys_active[KEY_E] = false;
                keys_up[KEY_E] = true;
                break;
            case ALLEGRO_KEY_R:
                keys_active[KEY_R] = false;
                keys_up[KEY_R] = true;
                break;
            case ALLEGRO_KEY_T:
                keys_active[KEY_T] = false;
                keys_up[KEY_T] = true;
                break;
            case ALLEGRO_KEY_Y:
                keys_active[KEY_Y] = false;
                keys_up[KEY_Y] = true;
                break;
            case ALLEGRO_KEY_U:
                keys_active[KEY_U] = false;
                keys_up[KEY_U] = true;
                break;
            case ALLEGRO_KEY_I:
                keys_active[KEY_I] = false;
                keys_up[KEY_I] = true;
                break;
            case ALLEGRO_KEY_O:
                keys_active[KEY_O] = false;
                keys_up[KEY_O] = true;
                break;
            case ALLEGRO_KEY_P:
                keys_active[KEY_P] = false;
                keys_up[KEY_P] = true;
                break;
            case ALLEGRO_KEY_A:
                keys_active[KEY_A] = false;
                keys_up[KEY_A] = true;
                break;
            case ALLEGRO_KEY_S:
                keys_active[KEY_S] = false;
                keys_up[KEY_S] = true;
                break;
            case ALLEGRO_KEY_D:
                keys_active[KEY_D] = false;
                keys_up[KEY_D] = true;
                break;
            case ALLEGRO_KEY_F:
                keys_active[KEY_F] = false;
                keys_up[KEY_F] = true;
                break;
            case ALLEGRO_KEY_G:
                keys_active[KEY_G] = false;
                keys_up[KEY_G] = true;
                break;
            case ALLEGRO_KEY_H:
                keys_active[KEY_H] = false;
                keys_up[KEY_H] = true;
                break;
            case ALLEGRO_KEY_J:
                keys_active[KEY_J] = false;
                keys_up[KEY_J] = true;
                break;
            case ALLEGRO_KEY_K:
                keys_active[KEY_K] = false;
                keys_up[KEY_K] = true;
                break;
            case ALLEGRO_KEY_L:
                keys_active[KEY_L] = false;
                keys_up[KEY_L] = true;
                break;
            case ALLEGRO_KEY_Z:
                keys_active[KEY_Z] = false;
                keys_up[KEY_Z] = true;
                break;
            case ALLEGRO_KEY_X:
                keys_active[KEY_X] = false;
                keys_up[KEY_X] = true;
                break;
            case ALLEGRO_KEY_C:
                keys_active[KEY_C] = false;
                keys_up[KEY_C] = true;
                break;
            case ALLEGRO_KEY_V:
                keys_active[KEY_V] = false;
                keys_up[KEY_V] = true;
                break;
            case ALLEGRO_KEY_B:
                keys_active[KEY_B] = false;
                keys_up[KEY_B] = true;
                break;
            case ALLEGRO_KEY_N:
                keys_active[KEY_N] = false;
                keys_up[KEY_N] = true;
                break;
            case ALLEGRO_KEY_M:
                keys_active[KEY_M] = false;
                keys_up[KEY_M] = true;
                break;
            case ALLEGRO_KEY_BACKSPACE:
                keys_active[KEY_BACKSPACE] = false;
                keys_up[KEY_BACKSPACE] = true;
                break;
            case ALLEGRO_KEY_RSHIFT:
                keys_active[KEY_RSHIFT] = false;
                keys_up[KEY_RSHIFT] = true;
                break;
        }
    }
}
