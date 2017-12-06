#include "sprite.h"
#include "hitbox.h"
#include "keyboard.h"
#include <stdbool.h>

typedef struct
{
    int velocity;
    int pos_x;
    int pos_y;
    int width;
    int height;
    Hitbox hitbox;
    Sprite sprite;
    // TODO: dodawac rzeczy kiedy beda potrzebne

} Player;

Player create_player(int pos_x, int pos_y, int width, int height, int velocity);
void draw_player(Player* player);
void update_player(Player* player, bool* key);
