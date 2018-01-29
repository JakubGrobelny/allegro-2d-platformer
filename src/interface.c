#include "interface.h"

ALLEGRO_FONT* font;

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
            al_draw_text(font, al_map_rgb(255, 255, 255), x, y, ALLEGRO_ALIGN_CENTRE, text->str);
            break;
        case ALIGNMENT_LEFT:
            al_draw_text(font, al_map_rgb(255, 255, 255), x, y, ALLEGRO_ALIGN_LEFT, text->str);
            break;
        case ALIGNMENT_RIGHT:
            al_draw_text(font, al_map_rgb(255, 255, 255), x, y, ALLEGRO_ALIGN_RIGHT, text->str);
            break;
    }

}
