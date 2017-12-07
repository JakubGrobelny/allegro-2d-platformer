#include "sprite.h"
#include "hitbox.h"
#include "keyboard.h"
#include <stdbool.h>

typedef struct
{
    int speed_vertical;
    int speed_horizontal;
    int pos_x;
    int pos_y;
    int width;
    int height;
    Hitbox hitbox;
    Sprite sprite;
    // TODO: dodawac rzeczy kiedy beda potrzebne

} Object;

Object create_object(int pos_x, int pos_y, int width, int height, int vel_vertical, int vel_horizontal);
void draw_object(Object* object);
void update_player(Object* player, bool* key);
