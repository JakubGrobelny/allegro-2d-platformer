#include "interface.h"

ALLEGRO_FONT* font;
ALLEGRO_BITMAP* coin_icon;

Button pause_menu_buttons[2];
int active_button;

void main_menu()
{
    
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

    if (keys_active[KEY_ENTER])
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
    pause_menu_buttons[UNPAUSE] = create_button(DISPLAY_WIDTH/2 - 256, 152, 512, 192, "CONITNUE");
    pause_menu_buttons[EXIT] = create_button(DISPLAY_WIDTH/2 - 256, 152 + 192 + 32, 512, 192, "EXIT");
    active_button = UNPAUSE;

    coin_icon = al_create_bitmap(64*5, 64);
    coin_icon = al_load_bitmap("./resources/textures/secret_brick.png");

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
