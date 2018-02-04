#include "editor.h"

LevelList* select_level(LevelList* level_list, ALLEGRO_EVENT_QUEUE* event_queue,  bool* keys_active, bool* keys_down, bool* keys_up)
{
    bool selected = false;
    char file_name[40] = "./level/";
    int i = 8;
    bool redraw = false;

    while (!selected)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        update_buttons(&event, keys_down, keys_up, keys_active);

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            if (i < 39)
            {
                if (keys_down[KEY_DOT])
                {
                    file_name[i] = '.';
                    i++;
                }
                else
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
            }

            if (i > 8)
            {
                if (keys_down[KEY_BACKSPACE])
                {
                    file_name[i - 1] = '\0';
                    i--;
                }
            }

            if (i > 8 && keys_down[KEY_ENTER])
                selected = true;

            reset_buttons(keys_down, keys_up, KEYS_AMOUNT);
        }

        if (redraw)
        {
            al_draw_filled_rectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, BLACK);
            draw_text(DISPLAY_WIDTH / 2, 32, ALIGNMENT_CENTRE, "Enter the file name:");
            draw_text(DISPLAY_WIDTH / 2, 128, ALIGNMENT_CENTRE, file_name);
            redraw = false;

            al_flip_display();
        }
    }

    LevelList* pointer = level_list;
    LevelList* previous;

    while(pointer)
    {
        if (compare_strings(pointer->path, file_name))
            break;

        if (pointer->next == NULL)
            previous = pointer;

        pointer = pointer->next;
    }

    if (!pointer)
    {
        FILE* file;

        file = fopen("./level/level_index", "a");
        fprintf(file, "%s\n", file_name);

        fclose(file);

        file = fopen(file_name, "w");

        for (int y = 0; y < MAP_HEIGHT*2; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                if(y != 10)
                    fprintf(file, "0");
                else
                    fprintf(file, "@");
            }
            fprintf(file, "\n");
        }

        fclose(file);

        pointer = create_list_element(file_name, previous);
        previous->next = pointer;

        return pointer;
    }
    else
        return pointer;
}

int move_screen(bool* keys_down, bool* keys_up, bool* keys_active)
{
    if (keys_active[KEY_LEFT])
        return -16;
    else if (keys_active[KEY_RIGHT])
        return 16;
    return 0;
}
