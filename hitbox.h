#include <stdbool.h>

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
bool collide(Hitbox first, Hitbox second, int tolerance);
