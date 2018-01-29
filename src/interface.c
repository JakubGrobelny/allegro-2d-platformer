#include "interface.h"

ALLEGRO_FONT* font;

String* lives_str;
    String* lives_str_text;
    String* lives_str_number;

String* coins_str;
    String* coins_str_text;
    String* coins_str_number;

ALLEGRO_BITMAP* coin_icon;

void draw_menu()
{

}

void update_menu(bool* paused)
{
    
}

void init_interface()
{
    lives_str = malloc(sizeof(String));
    lives_str_text = malloc(sizeof(String));
    lives_str_number = malloc(sizeof(String));
    coins_str = malloc(sizeof(String));
    coins_str_text = malloc(sizeof(String));
    coins_str_number = malloc(sizeof(String));

    init_string(lives_str, 1);
    set_string(lives_str_text, "MARIO x ");
    init_string(lives_str_number, 1);
    init_string(coins_str, 1);
    set_string(coins_str_text, " x ");
    init_string(coins_str_number, 1);

    coin_icon = al_create_bitmap(64*5, 64);
    coin_icon = al_load_bitmap("./resources/textures/secret_brick.png");

    load_font("./resources/fonts/PressStart2P.ttf");
}

void draw_hud(int lives, int coins)
{
    int_to_string(lives_str_number, lives);
    int_to_string(coins_str_number, coins);

    concatenate(lives_str, lives_str_text, lives_str_number);
    concatenate(coins_str, coins_str_text, coins_str_number);

    draw_text(24, 24, ALIGNMENT_LEFT, lives_str);
    draw_text(DISPLAY_WIDTH - 64 - 256 + 16, 24, ALIGNMENT_LEFT, coins_str);
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

void draw_text(int x, int y, int alignment, String* text)
{
    switch (alignment)
    {
        case ALIGNMENT_CENTRE:
            al_draw_text(font, WHITE, x, y, ALLEGRO_ALIGN_CENTRE, text->str);
            break;
        case ALIGNMENT_LEFT:
            al_draw_text(font, WHITE, x, y, ALLEGRO_ALIGN_LEFT, text->str);
            break;
        case ALIGNMENT_RIGHT:
            al_draw_text(font, WHITE, x, y, ALLEGRO_ALIGN_RIGHT, text->str);
            break;
    }

}
