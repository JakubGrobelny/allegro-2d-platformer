#include "interface.h"

ALLEGRO_FONT* font;
ALLEGRO_BITMAP* coin_icon;

Button pause_menu_buttons[2];
int active_button;

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
