#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include "defines.h"

#ifndef _HITBOX
#define _HITBOX

enum types
{
    /*
    enum containing possible types of hitboxes
     */

    RECTANGLE,
};

typedef struct
{
    /*
    Structure responsible for finding collisions between objects
     */

    short type; // shape of the hitbox
    int pos_x;  // x coordinate of the top-left corner of the hitbox (or its center if it's a circle)
    int pos_y;  // y coordinate of the top-left corner of the hitbox (or its center if it's a circle)
    int width;  // width of the hitbox (or its radius if it's a circle)
    int height; // height of the hitbox (or its radius if it's a circle)

} Hitbox;

// creating new hitbox with given parameters
Hitbox create_hitbox(short type, int pos_x, int pos_y, int width, int height);

// checking if two hitboxes collide
bool collide(Hitbox first, Hitbox second);

// checking if two hitboxes collide but only in x axis
bool collide_x(Hitbox first, Hitbox second);

// checking if two hitboxes collide but only in y axis
bool collide_y(Hitbox first, Hitbox second);

// drawing a hitbox for debuggings
void draw_hitbox(Hitbox hitbox, int screen_offset);

#endif
