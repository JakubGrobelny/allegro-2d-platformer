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

} Player;

Player create_player(int pos_x, int pos_y, int width, int height, int vel_vertical, int vel_horizontal);
void draw_player(Player* player);
void update_player(Player* player, bool* key);
