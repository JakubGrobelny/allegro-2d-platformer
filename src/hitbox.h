#include <stdbool.h>

#ifndef _HITBOX
#define _HITBOX

enum types
{
    rectangle,
    circle
};

typedef struct
{
    short type;
    int pos_x;
    int pos_y;
    int width;
    int height;

} Hitbox;

Hitbox create_hitbox(short type, int pos_x, int pos_y, int width, int height);
bool collide(Hitbox first, Hitbox second);
#endif