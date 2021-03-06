#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "defines.h"
#include "bitmap.h"
#include "object.h"
#include "keyboard.h"
#include "level.h"

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
int active_button;

Button editor_pause_menu_buttons[3]; // 0 - unpause, 1 - save, 2 - exit
int editor_pause_menu_active_button;

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

typedef enum
{
    EDITOR_UNPAUSE,
    EDITOR_SAVE,
    EDITOR_EXIT
} EditorPauseButtonTypes;

// draws and updates the main menu
void main_menu(ALLEGRO_EVENT_QUEUE* event_queue, bool* exit, bool* editor, bool* keys_active, bool* keys_down, bool* keys_up);

// creates a new button
Button create_button(int x, int y, int width, int height, char* text);

// draws a game over screen when you don't have any lives remaining
void draw_game_over_screen();

// draws information about the next level to the screen
void draw_next_level_screen(char* path);

// draws a screen after the player finishes the game
void draw_congratulations_screen();

// draws pause menu but for editor mode
void draw_editor_pause_menu();

// draws editor information
void draw_editor_hud(int selected_layer, int selected_object, int x, int y);

// draws 64x64 grid
void draw_grid(int screen_offset);

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

// updates menu based on mouse/keyboard input
void update_editor_pause_menu(bool* paused, bool* exit, bool* keys_active, bool* keys_down, LevelList* current_level, Object level[MAP_HEIGHT][MAP_WIDTH], Object background[MAP_HEIGHT][MAP_WIDTH], ObjectsList* non_static_elements);

#endif
