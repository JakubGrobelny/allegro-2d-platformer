#include "editor.h"

LevelList* select_level(LevelList* level_list, ALLEGRO_EVENT_QUEUE* event_queue,  bool* keys_active, bool* keys_down, bool* keys_up)
{
    bool selected = false;
    char file_name[256];
    memset(file_name, '\0', 256);

    int i = 0;
    bool redraw = false;

    while (!selected)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        update_buttons(&event, keys_down, keys_up, keys_active);

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            if (i < 255)
            {
                for (int key = KEY_A; key <= KEY_Z; key++)
                {
                    if (keys_down[key])
                    {
                        if (keys_active[KEY_RSHIFT])
                        file_name[i] = 'A' + key;
                        else
                        file_name[i] = 'a' + key;
                        i++;
                        break;
                    }
                }
            }

            if (i > 0)
            {
                if (keys_down[KEY_BACKSPACE])
                {
                    file_name[i - 1] = '\0';
                    i--;
                }
            }

            if (i > 0 && keys_down[KEY_ENTER])
                selected = true;

            reset_buttons(keys_down, keys_up, KEYS_AMOUNT);
        }

        if (redraw)
        {
            al_draw_filled_rectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, BLACK);
            draw_text(DISPLAY_WIDTH / 2, 32, ALIGNMENT_CENTRE, "Enter the file name: ");
            draw_text(DISPLAY_WIDTH / 2, 128, ALIGNMENT_CENTRE, file_name);
            redraw = false;

            al_flip_display();
        }
    }
}
