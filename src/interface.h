#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "defines.h"
#include "keyboard.h"

#ifndef _INTERFACE
#define _INTERFACE

#define FONT_SIZE 32

extern ALLEGRO_FONT* font;

extern ALLEGRO_MOUSE_STATE mouse_state;
ALLEGRO_BITMAP* coin_icon;

ALLEGRO_BITMAP* main_menu_bg;
ALLEGRO_BITMAP* main_menu_pointer;

typedef struct Button
{
    int pos_x;
    int pos_y;
    int width;
    int height;
    char* text;

} Button;

Button pause_menu_buttons[2]; // 0 - unpause, 1 - exit
Button main_menu_buttons[3];
int active_button;

typedef enum
{
    ALIGNMENT_CENTRE,
    ALIGNMENT_LEFT,
    ALIGNMENT_RIGHT

} Alignments;

typedef enum
{
    UNPAUSE = 0,
    EXIT = 1

} PauseButtonTypes;

typedef enum
{
    MENU_START,
    MENU_EDITOR,
    MENU_EXIT
} MenuButtonTypes;

// draws and updates the main menu
void main_menu(ALLEGRO_EVENT_QUEUE* event_queue, bool* exit, bool* editor, bool* keys_active, bool* keys_down, bool* keys_up);

// creates a new button
Button create_button(int x, int y, int width, int height, char* text);

// draws a button
void draw_button(Button* button, bool active);

// initializes interface (whatever that means)
void init_interface();

// prints information like amount of lives left and number of coins
void draw_hud(int lives, int coins);

// loads the font from the given path
void load_font(char* path);

// prints text to the screen
void draw_text(int x, int y, int alignment, char* text); // TODO: add font choice

// draws buttons and stuff
void draw_pause_menu();

// updates menu based on mouse/keyboard input
void update_pause_menu(bool* paused, bool* exit, bool* keys_active, bool* keys_down, bool* keys_up);

#endif
