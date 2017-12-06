#include "sprite.h"
#include "hitbox.h"

typedef struct
{
    int pos_x;
    int pos_y;
    int width;
    int height;
    Hitbox hitbox;
    Sprite sprite;
    // TODO: dodawac rzeczy kiedy beda potrzebne

} Player;

Player create_player(int pos_x, int pos_y, int width, int height);
void draw_player(Player* player);
