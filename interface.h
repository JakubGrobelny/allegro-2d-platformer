#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>


#ifndef _INTERFACE
#define _INTERFACE

#define FONT_SIZE 32

extern ALLEGRO_FONT* font;

typedef enum
{
    ALIGNMENT_CENTRE,
    ALIGNMENT_LEFT,
    ALIGNMENT_RIGHT

} Alignments;

// loads the font from the given path
void load_font(char* path);

// prints text to the screen
void draw_text(int x, int y, int alignment, char* text);

#endif
