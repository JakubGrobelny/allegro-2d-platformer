#ifndef _OBJECT
#define _OBJECT

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>
#include "hitbox.h"
#include "keyboard.h"
#include "physics.h"

extern int lives;
extern int coins;

typedef struct
{
    /*
    Structure responsible for representing any type of object in the game
     */

    int pos_x;  // top-left corner x coordinate
    int pos_y;  // top-left corner y coordinate
    int type;   // type of the object

    ALLEGRO_BITMAP* bitmap;     // object's texture
    int width;                  // width of both the object and its bitmap
    int height;                 // height of both the object and its bitmap
    short animation_frame;      // current frame of the animation
    short frames_number;        // amount of the frames in the object's animation

    bool alive;                 // the state of object
    int counter;                // variable that will hold various things like object's lifetime

    Hitbox hitbox;      // object's hitbox
    Physics physics;    // structure that holds the object's physical properties

} Object;

typedef enum
{
    /*
    Enum of directions used to find relative position of two objects
     */
    STATIC = -1,
    TOP = 0,
    BOTTOM = 1,
    LEFT = 2,
    RIGHT = 3

} Directions;

typedef enum
{
    /*
    Enum of possible types of objects
     */

    //enemies
    ENEMY_GOOMBA,
    ENEMY_KOOPA,
    ENEMY_KOOPA_FLYING,
    ENEMY_PIRANHA_PLANT,
    //player
    PLAYER,
    PLAYER_BIG,
    EMPTY,
    //blocks
    NORMAL_BLOCK,
    UNBREAKABLE_BLOCK,
    SECRET_BLOCK,
    SECRET_BLOCK_MUSHROOM,
    BACKGROUND,
    CANNON_LEFT,
    CANNON_RIGHT,
    //spawned
    BULLET,
    KOOPA_SHELL,
    PARTICLE_NORMAL,
    SIZE_MUSHROOM,
    COIN,
    FINISH_LINE

} ObjectTypes;

// initializes the object with given parameters
void init_object(Object* object, int type, int pos_x, int pos_y, int width, int height, int hitbox_type, int hitbox_pos_x, int hitbox_pos_y, int hitbox_width, int hitbox_height, Physics physics, short frames_number);

// adding the pointer to bitmap to the object
void bind_bitmap(Object* object, ALLEGRO_BITMAP* bitmap);

// drawing object's bitmap
void draw_object(Object* object, int screen_offset);

// checking whether the object is in the given direction relatively to the observer
bool relative_direction(Object* observer, Object* object, int direction);

// making the given object stationary
void terminate_velocity(Object* object);

#endif
