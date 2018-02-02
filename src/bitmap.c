#include "bitmap.h"

void init_bitmaps()
{
    bitmap_cloud =                     al_create_bitmap(256, 256       );
    bitmap_plant =                     al_create_bitmap(128, 128 * 4   );
    bitmap_cannon =                    al_create_bitmap(64,  256       );
    bitmap_pipe_left =                 al_create_bitmap(64,  64        );
    bitmap_pipe_right =                al_create_bitmap(64,  64        );
    bitmap_enemy_koopa =               al_create_bitmap(96,  80*7      );
    bitmap_brick_floor =               al_create_bitmap(64,  64        );
    bitmap_brick =                     al_create_bitmap(64,  64        );
    bitmap_secret_brick =              al_create_bitmap(64,  64*5      );
    bitmap_enemy_goomba =              al_create_bitmap(64,  64*3      );
    bitmap_pipe_top_left =             al_create_bitmap(64,  64        );
    bitmap_pipe_top_right =            al_create_bitmap(64,  64        );
    bitmap_brick_unbreakable =         al_create_bitmap(64,  64        );

    bitmap_cloud =                     al_load_bitmap("./resources/textures.cloud.png");
    bitmap_plant =                     al_load_bitmap("./resources/textures/flower.png");
    bitmap_cannon =                    al_load_bitmap("./resources/textures/cannon.png");
    bitmap_pipe_left =                 al_load_bitmap("./resources/textures/pipe_left.png");
    bitmap_pipe_right =                al_load_bitmap("./resources/textures/pipe_right.png");
    bitmap_enemy_koopa =               al_load_bitmap("./resources/textures/enemy_2.png");
    bitmap_brick_floor =               al_load_bitmap("./resources/textures/orange_rock.png");
    bitmap_brick =                     al_load_bitmap("./resources/textures/brick_orange.png");
    bitmap_secret_brick =              al_load_bitmap("./resources/textures/secret_brick.png");
    bitmap_enemy_goomba =              al_load_bitmap("./resources/textures/enemy_1.png");
    bitmap_pipe_top_left =             al_load_bitmap("./resources/textures/pipe_top_left.png");
    bitmap_pipe_top_right =            al_load_bitmap("./resources/textures/pipe_top_right.png");
    bitmap_brick_unbreakable =         al_load_bitmap("./resources/textures/brick_orange_unbreakable.png");
}
