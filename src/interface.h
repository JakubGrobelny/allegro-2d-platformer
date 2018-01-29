#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <string.h>

#include "string.h"
#include "defines.h"

#ifndef _INTERFACE
#define _INTERFACE

#define FONT_SIZE 32

extern ALLEGRO_FONT* font;

String* lives_str;
    String* lives_str_text;
    String* lives_str_number;

String* coins_str;
    String* coins_str_text;
    String* coins_str_number;

ALLEGRO_BITMAP* coin_icon;

typedef enum
{
    ALIGNMENT_CENTRE,
    ALIGNMENT_LEFT,
    ALIGNMENT_RIGHT

} Alignments;

// initializes interface (whatever that means)
void init_interface();

// prints information like amount of lives left and number of coins
void draw_hud(int lives, int coins);

// loads the font from the given path
void load_font(char* path);

// prints text to the screen
void draw_text(int x, int y, int alignment, String* text); // TODO: add font choice

#endif
