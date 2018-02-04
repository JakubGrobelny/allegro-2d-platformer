#include "bitmap.h"

ALLEGRO_BITMAP* bitmap_brick;
ALLEGRO_BITMAP* bitmap_brick_unbreakable;
ALLEGRO_BITMAP* bitmap_brick_floor;
ALLEGRO_BITMAP* bitmap_secret_brick;
ALLEGRO_BITMAP* bitmap_cloud;
ALLEGRO_BITMAP* bitmap_cloud_big;
ALLEGRO_BITMAP* bitmap_enemy_goomba;
ALLEGRO_BITMAP* bitmap_enemy_koopa;
ALLEGRO_BITMAP* bitmap_plant;
ALLEGRO_BITMAP* bitmap_pipe_top_left;
ALLEGRO_BITMAP* bitmap_pipe_top_right;
ALLEGRO_BITMAP* bitmap_pipe_left;
ALLEGRO_BITMAP* bitmap_pipe_right;
ALLEGRO_BITMAP* bitmap_cannon;
ALLEGRO_BITMAP* bitmap_bush;
ALLEGRO_BITMAP* bitmap_bush_big;
ALLEGRO_BITMAP* bitmap_fence;
ALLEGRO_BITMAP* bitmap_hill_top;
ALLEGRO_BITMAP* bitmap_hill_middle_patterned_right;
ALLEGRO_BITMAP* bitmap_hill_middle_patterned_left;
ALLEGRO_BITMAP* bitmap_hill_middle;
ALLEGRO_BITMAP* bitmap_hill_slope_right;
ALLEGRO_BITMAP* bitmap_hill_slope_left;
ALLEGRO_BITMAP* bitmap_tree_bottom;
ALLEGRO_BITMAP* bitmap_tree_small;
ALLEGRO_BITMAP* bitmap_tree;
ALLEGRO_BITMAP* bitmap_finish_flag;
ALLEGRO_BITMAP* player_bitmap;
ALLEGRO_BITMAP* player_big_bitmap;

void init_bitmaps()
{
    bitmap_cloud = al_create_bitmap(256, 256);
    bitmap_plant = al_create_bitmap(128, 128 * 4);
    bitmap_cannon = al_create_bitmap(64, 256);
    bitmap_pipe_left = al_create_bitmap(64, 64);
    bitmap_pipe_right = al_create_bitmap(64, 64);
    bitmap_enemy_koopa = al_create_bitmap(96, 80*7);
    bitmap_brick_floor = al_create_bitmap(64, 64);
    bitmap_brick = al_create_bitmap(64, 64);
    bitmap_secret_brick = al_create_bitmap(64, 64*5);
    bitmap_enemy_goomba = al_create_bitmap(64, 64*3);
    bitmap_pipe_top_left = al_create_bitmap(64, 64);
    bitmap_pipe_top_right = al_create_bitmap(64, 64);
    bitmap_brick_unbreakable = al_create_bitmap(64, 64);
    bitmap_cloud = al_create_bitmap(128, 128);
    bitmap_cloud_big = al_create_bitmap(192, 128);
    bitmap_bush = al_create_bitmap(128, 64);
    bitmap_bush_big = al_create_bitmap(192, 68);
    bitmap_fence = al_create_bitmap(64, 64);
    bitmap_hill_top = al_create_bitmap(64, 64);
    bitmap_hill_middle_patterned_right = al_create_bitmap(64, 64);
    bitmap_hill_middle_patterned_left = al_create_bitmap(64, 64);
    bitmap_hill_middle = al_create_bitmap(64, 64);
    bitmap_hill_slope_right = al_create_bitmap(64, 64);
    bitmap_hill_slope_left = al_create_bitmap(64, 64);
    bitmap_tree_bottom = al_create_bitmap(64, 64);
    bitmap_tree_small = al_create_bitmap(64, 64);
    bitmap_tree = al_create_bitmap(64, 128);
    bitmap_finish_flag = al_create_bitmap(64, 128);
    player_bitmap = al_create_bitmap(64, 64 * 15);
    player_big_bitmap = al_create_bitmap(64, 128 * 17);

    bitmap_cloud = al_load_bitmap("./resources/textures.cloud.png");
    bitmap_plant = al_load_bitmap("./resources/textures/flower.png");
    bitmap_cannon = al_load_bitmap("./resources/textures/cannon.png");
    bitmap_pipe_left = al_load_bitmap("./resources/textures/pipe_left.png");
    bitmap_pipe_right = al_load_bitmap("./resources/textures/pipe_right.png");
    bitmap_enemy_koopa = al_load_bitmap("./resources/textures/enemy_2.png");
    bitmap_brick_floor = al_load_bitmap("./resources/textures/orange_rock.png");
    bitmap_brick = al_load_bitmap("./resources/textures/brick_orange.png");
    bitmap_secret_brick = al_load_bitmap("./resources/textures/secret_brick.png");
    bitmap_enemy_goomba = al_load_bitmap("./resources/textures/enemy_1.png");
    bitmap_pipe_top_left = al_load_bitmap("./resources/textures/pipe_top_left.png");
    bitmap_pipe_top_right = al_load_bitmap("./resources/textures/pipe_top_right.png");
    bitmap_brick_unbreakable = al_load_bitmap("./resources/textures/brick_orange_unbreakable.png");
    bitmap_cloud = al_load_bitmap("./resources/textures/cloud.png");
    bitmap_cloud_big = al_load_bitmap("./resources/textures/cloud_big.png");
    bitmap_bush = al_load_bitmap("./resources/textures/bush.png");
    bitmap_bush_big = al_load_bitmap("./resources/textures/bush_big.png");
    bitmap_fence = al_load_bitmap("./resources/textures/fence.png");
    bitmap_hill_top = al_load_bitmap("./resources/textures/hill_top.png");
    bitmap_hill_middle_patterned_right = al_load_bitmap("./resources/textures/hill_mid_pattern_r.png");
    bitmap_hill_middle_patterned_left = al_load_bitmap("./resources/textures/hill_mid_pattern_l.png");
    bitmap_hill_middle = al_load_bitmap("./resources/textures/hill_mid.png");
    bitmap_hill_slope_right = al_load_bitmap("./resources/textures/hill_slope_r.png");
    bitmap_hill_slope_left = al_load_bitmap("./resources/textures/hill_slope_l.png");
    bitmap_tree_bottom = al_load_bitmap("./resources/textures/tree_bottom.png");
    bitmap_tree_small = al_load_bitmap("./resources/textures/tree_small.png");
    bitmap_tree = al_load_bitmap("./resources/textures/tree.png");
    bitmap_finish_flag = al_load_bitmap("./resources/textures/end_flag.png");
    player_bitmap = al_load_bitmap("./resources/textures/mario_small.png");
    player_big_bitmap = al_load_bitmap("./resources/textures/mario_big.png");
}

void destroy_bitmaps()
{

}
