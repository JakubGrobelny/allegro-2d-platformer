#include "sprite.h"
#include "hitbox.h"
#include "keyboard.h"
#include <stdbool.h>
#include "physics.h"

typedef struct
{
    int pos_x;
    int pos_y;
    int width;
    int height;
    Hitbox hitbox;
    Sprite sprite;
    Physics physics; // TODO: fizyka
    int type;
    // TODO: dodawac rzeczy kiedy beda potrzebne

} Object;

Object create_object(int pos_x, int pos_y, int width, int height, Physics physics, int type);
void draw_object(Object* object);
void update_player(Object* player, bool* key);
