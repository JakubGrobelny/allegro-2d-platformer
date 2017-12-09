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
        }
    }
}
