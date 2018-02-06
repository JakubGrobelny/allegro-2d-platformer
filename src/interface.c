#include "interface.h"

ALLEGRO_FONT* font;
ALLEGRO_BITMAP* coin_icon;

Button pause_menu_buttons[2];
int active_button;

Button editor_pause_menu_buttons[3];
int editor_pause_menu_active_button;

ALLEGRO_MOUSE_STATE mouse_state;

void main_menu(ALLEGRO_EVENT_QUEUE* event_queue, bool* exit, bool* editor, bool* keys_active, bool* keys_down, bool* keys_up)
{
    char* main_menu_text[3] = {"START", "LEVEL EDITOR", "EXIT"};
    char* main_menu_text_active[3] = {">START<", ">LEVEL EDITOR<", ">EXIT<"};

    int pointer_x = 64 + 276 + 16;
    int menu_active_button = MENU_START;

    bool draw = false;

    while (!*exit)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        update_buttons(&event, keys_down, keys_up, keys_active);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *exit = true;
            break;
        }

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            if (keys_down[KEY_UP])
                menu_active_button--;
            else if (keys_down[KEY_DOWN])
                menu_active_button++;

            if (menu_active_button < MENU_START)
                menu_active_button = MENU_EXIT;
            else if (menu_active_button > MENU_EXIT)
                menu_active_button = MENU_START;

            if (keys_active[KEY_ENTER])
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
            draw = true;
        }

        if (draw)
        {
            draw = false;

            al_draw_bitmap(main_menu_bg, 0, 0, 0);

            for (int i = 0; i < 3; i++)
                draw_text(DISPLAY_WIDTH / 2, 400 + i * 64 ,ALIGNMENT_CENTRE, menu_active_button == i ? main_menu_text_active[i] : main_menu_text[i]);

            al_flip_display();
        }
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

void draw_game_over_screen()
{
    al_draw_filled_rectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, BLACK);
    draw_text(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALIGNMENT_CENTRE, "GAME OVER");
}

void draw_congratulations_screen()
{
    al_draw_filled_rectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, BLACK);
    draw_text(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALIGNMENT_CENTRE, "CONGRATULATIONS!");
    draw_text(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 + 64, ALIGNMENT_CENTRE, "You finished the game!");
}

void draw_grid(int screen_offset)
{
    for (int x = 0; x <= MAP_WIDTH; x++)
        al_draw_line(x*64 - screen_offset, 16, x*64 - screen_offset, MAP_HEIGHT*64 + 16, BLACK, 0.0f);
    for (int y = 0; y <= MAP_HEIGHT; y++)
        al_draw_line(0 - screen_offset, y*64 + 16, MAP_WIDTH*64 - screen_offset, y*64 + 16, BLACK, 0.0f);
}

void draw_next_level_screen(char* path)
{
    al_draw_filled_rectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, BLACK);
    char shortened_path[256];

    int i = 8;

    do
    {
        shortened_path[i - 8] = path[i];
        i++;
    }
    while (path[i] != '\0');

    i-=8;

    shortened_path[i-4] = '\0';

    draw_text(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 - 128, ALIGNMENT_CENTRE, shortened_path);

    al_draw_bitmap_region(player_bitmap, 0, 0, 64, 64, DISPLAY_WIDTH / 2 - 128, DISPLAY_HEIGHT / 2 - 64, 0);
    al_draw_textf(font, WHITE, DISPLAY_WIDTH /2 - 64, DISPLAY_HEIGHT / 2 - 64, ALLEGRO_ALIGN_LEFT, " x %d", lives);
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

void draw_editor_pause_menu()
{
    al_draw_filled_rectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, al_map_rgba(64, 64, 64, 200));

    for (int i = 0; i < 3; i++)
    {
        if (i == editor_pause_menu_active_button)
            draw_button(&editor_pause_menu_buttons[i], true);
        else
            draw_button(&editor_pause_menu_buttons[i], false);
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

void draw_editor_hud(int selected_layer, int selected_object, int x, int y)
{
    al_draw_textf(font, WHITE, 16, 16, ALLEGRO_ALIGN_LEFT, "LAYER: %s  X: %d  Y: %d", selected_layer == 0 ? "MAP" : selected_layer == 1 ? "BACKGROUND" : "OBJECTS" , x, y);

    if (selected_layer == 0)
    {
        if (selected_object == 3)
        al_draw_textf(font, WHITE, 16, 48, ALLEGRO_ALIGN_LEFT, "1 COIN BLOCK");
        else if (selected_object == 4)
        al_draw_textf(font, WHITE, 16, 48, ALLEGRO_ALIGN_LEFT, "MUSHROOM BLOCK");
        else if (selected_object == 5)
        al_draw_textf(font, WHITE, 16, 48, ALLEGRO_ALIGN_LEFT, "5 COINS BLOCK");
        else if (selected_object == 6)
        al_draw_textf(font, WHITE, 16, 48, ALLEGRO_ALIGN_LEFT, "CANNON RIGHT");
        else if (selected_object == 7)
        al_draw_textf(font, WHITE, 16, 48, ALLEGRO_ALIGN_LEFT, "CANNON LEFT");
    }
}

void update_editor_pause_menu(bool* paused, bool* exit, bool* keys_active, bool* keys_down, LevelList* current_level, Object level[MAP_HEIGHT][MAP_WIDTH], Object background[MAP_HEIGHT][MAP_WIDTH], ObjectsList* non_static_elements)
{
    if (keys_down[KEY_UP])
        editor_pause_menu_active_button--;
    else if (keys_down[KEY_DOWN])
        editor_pause_menu_active_button++;

    if (editor_pause_menu_active_button < EDITOR_UNPAUSE)
        editor_pause_menu_active_button = EDITOR_UNPAUSE;
    else if (editor_pause_menu_active_button > EDITOR_EXIT)
        editor_pause_menu_active_button = EDITOR_EXIT;

    bool mouse_on_button = false;

    for (int i = 0; i < 3; i++)
    {
        if (mouse_state.x >= editor_pause_menu_buttons[i].pos_x && mouse_state.x <= editor_pause_menu_buttons[i].pos_x + editor_pause_menu_buttons[i].width)
        {
            if (mouse_state.y >= editor_pause_menu_buttons[i].pos_y && mouse_state.y <= editor_pause_menu_buttons[i].pos_y + editor_pause_menu_buttons[i].height)
            {
                editor_pause_menu_active_button = i;
                mouse_on_button = true;
            }
        }
    }

    if (keys_active[KEY_ENTER] || (mouse_state.buttons & 1 && mouse_on_button))
    {
        switch (editor_pause_menu_active_button)
        {
            case EDITOR_UNPAUSE:
                *paused = false;
                break;
            case EDITOR_SAVE:
                save_level(current_level, level, background, non_static_elements);
                *paused = false;
                break;
            case EDITOR_EXIT:
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
    editor_pause_menu_active_button = 0;

    pause_menu_buttons[UNPAUSE] = create_button(DISPLAY_WIDTH/2 - 256, 152, 512, 192, "CONTINUE");
    pause_menu_buttons[EXIT] = create_button(DISPLAY_WIDTH/2 - 256, 152 + 192 + 32, 512, 192, "EXIT");

    editor_pause_menu_buttons[EDITOR_UNPAUSE] = create_button(DISPLAY_WIDTH / 2 - 256, 128, 512, 148, "CONTINUE");
    editor_pause_menu_buttons[EDITOR_SAVE] = create_button(DISPLAY_WIDTH / 2 - 256, 128 + 148 + 32, 512, 148, "SAVE");
    editor_pause_menu_buttons[EDITOR_EXIT] = create_button(DISPLAY_WIDTH / 2 - 256, 128 + 2*148 + 64, 512, 148, "EXIT");

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
