#include "interface.h"

ALLEGRO_FONT* font;
ALLEGRO_BITMAP* coin_icon;

Button pause_menu_buttons[2];
int active_button;

ALLEGRO_MOUSE_STATE mouse_state;

void main_menu(ALLEGRO_EVENT_QUEUE* event_queue, bool* exit, bool* editor, bool* keys_active, bool* keys_down, bool* keys_up)
{
    int pointer_x = 64 + 276 + 16;
    int menu_active_button = MENU_START;

    while (!*exit)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        al_get_mouse_state(&mouse_state);
        update_buttons(&event, keys_down, keys_up, keys_active);

        // it's pretty much update_pause_menu()
        if (keys_down[KEY_UP])
            menu_active_button--;
        else if (keys_down[KEY_DOWN])
            menu_active_button++;

        if (menu_active_button < MENU_START)
            active_button = MENU_START;
        else if (menu_active_button > MENU_EXIT)
            active_button = MENU_EXIT;

        bool mouse_on_button = false;

        for (int i = 0; i < 3; i++)
        {
            if (mouse_state.x >= pause_menu_buttons[i].pos_x && mouse_state.x <= pause_menu_buttons[i].pos_x + pause_menu_buttons[i].width)
            {
                if (mouse_state.y >= pause_menu_buttons[i].pos_y && mouse_state.y <= pause_menu_buttons[i].pos_y + pause_menu_buttons[i].height)
                {
                    menu_active_button = i;
                    mouse_on_button = true;
                }
            }
        }

        if (keys_active[KEY_ENTER] || (mouse_state.buttons & 1 && mouse_on_button))
        {
            switch (menu_active_button)
            {
                case MENU_START:
                    return;
                case MENU_EXIT:
                    *exit = true;
                    return;
                case MENU_EDITOR:
                    *editor = true;
                    return;
            }
        }
        reset_buttons(keys_down, keys_up, KEYS_AMOUNT);

        int pointer_y = main_menu_buttons[menu_active_button].pos_y + main_menu_buttons[menu_active_button].height / 2;

        al_draw_bitmap(main_menu_bg, 0, 0, 0);
        al_draw_bitmap(main_menu_pointer, pointer_x, pointer_y, 0);
        al_flip_display();
    }

    al_destroy_bitmap(main_menu_bg);
    al_destroy_bitmap(main_menu_pointer);
}

void draw_button(Button* button, bool active)
{
    if (active)
        al_draw_filled_rectangle(button->pos_x - 16, button->pos_y - 16, button->pos_x + button->width + 16, button->pos_y + button->height + 16, al_map_rgb(0, 0, 0));
    al_draw_filled_rectangle(button->pos_x, button->pos_y, button->pos_x + button->width, button->pos_y + button->height, al_map_rgb(174, 78, 0));

    draw_text(button->pos_x + button->width/2, button->pos_y + button->height/2, ALIGNMENT_CENTRE, button->text);
}

void draw_pause_menu()
{
    al_draw_filled_rectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, al_map_rgba(64, 64, 64, 200));

    for (int i = 0; i < 2; i++)
    {
        if (i == active_button)
            draw_button(&pause_menu_buttons[i], true);
        else
            draw_button(&pause_menu_buttons[i], false);
    }

}

void update_pause_menu(bool* paused, bool* exit, bool* keys_active, bool* keys_down, bool* keys_up)
{
    if (keys_down[KEY_UP])
        active_button--;
    else if (keys_down[KEY_DOWN])
        active_button++;

    if (active_button < UNPAUSE)
        active_button = UNPAUSE;
    else if (active_button > EXIT)
        active_button = EXIT;

    bool mouse_on_button = false;

    for (int i = 0; i < 2; i++)
    {
        if (mouse_state.x >= pause_menu_buttons[i].pos_x && mouse_state.x <= pause_menu_buttons[i].pos_x + pause_menu_buttons[i].width)
        {
            if (mouse_state.y >= pause_menu_buttons[i].pos_y && mouse_state.y <= pause_menu_buttons[i].pos_y + pause_menu_buttons[i].height)
            {
                active_button = i;
                mouse_on_button = true;
            }
        }
    }

    if (keys_active[KEY_ENTER] || (mouse_state.buttons & 1 && mouse_on_button))
    {
        switch (active_button)
        {
            case UNPAUSE:
                *paused = false;
                break;
            case EXIT:
                *exit = true;
                break;
        }
    }
}

Button create_button(int x, int y, int width, int height, char* text)
{
    Button new;

    new.pos_x = x;
    new.pos_y = y;
    new.width = width;
    new.height = height;
    new.text = text;

    return new;
}

void init_interface()
{
    active_button = 0;

    pause_menu_buttons[UNPAUSE] = create_button(DISPLAY_WIDTH/2 - 256, 152, 512, 192, "CONTINUE");
    pause_menu_buttons[EXIT] = create_button(DISPLAY_WIDTH/2 - 256, 152 + 192 + 32, 512, 192, "EXIT");

    main_menu_buttons[MENU_START] = create_button(64, 64, 276, 176, "START");
    main_menu_buttons[MENU_EDITOR] = create_button(64, 64  + 32 + 176, 276, 176, "EDITOR");
    main_menu_buttons[MENU_EXIT] = create_button(64, 64 + 32 + 176 + 32 + 176, 276, 176, "EXIT");

    coin_icon = al_create_bitmap(64*5, 64);
    coin_icon = al_load_bitmap("./resources/textures/secret_brick.png");

    main_menu_bg = al_create_bitmap(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    main_menu_pointer = al_create_bitmap(64, 64);
    main_menu_bg = al_load_bitmap("./resources/textures/main_menu_bg.png");
    main_menu_pointer = al_load_bitmap("./resources/textures/main_menu_pointer.png");

    load_font("./resources/fonts/PressStart2P.ttf");
}

void draw_hud(int lives, int coins)
{
    al_draw_textf(font, WHITE, 24, 24, ALLEGRO_ALIGN_LEFT, "MARIO x %d", lives);
    al_draw_textf(font, WHITE, DISPLAY_WIDTH - 64 - 256 + 16, 24, ALLEGRO_ALIGN_LEFT, " x %d", coins);

    al_draw_bitmap_region(coin_icon, 0, 3*64, 64, 64, DISPLAY_WIDTH - 16 - 64 - 256, 8, 0);
}

void load_font(char* path)
{
    font = al_load_ttf_font(path, FONT_SIZE, 0);

    if (!font)
    {
        printf("Failed to load font from %s\n", path);
        exit(-1);
    }
}

void draw_text(int x, int y, int alignment, char* text)
{
    switch (alignment)
    {
        case ALIGNMENT_CENTRE:
            al_draw_text(font, WHITE, x, y, ALLEGRO_ALIGN_CENTRE, text);
            break;
        case ALIGNMENT_LEFT:
            al_draw_text(font, WHITE, x, y, ALLEGRO_ALIGN_LEFT, text);
            break;
        case ALIGNMENT_RIGHT:
            al_draw_text(font, WHITE, x, y, ALLEGRO_ALIGN_RIGHT, text);
            break;
    }

}
