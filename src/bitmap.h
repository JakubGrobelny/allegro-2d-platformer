#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#ifndef _BITMAP
#define _BITMAP

// MAP
extern ALLEGRO_BITMAP* bitmap_brick;
extern ALLEGRO_BITMAP* bitmap_brick_unbreakable;
extern ALLEGRO_BITMAP* bitmap_brick_floor;
extern ALLEGRO_BITMAP* bitmap_secret_brick;
extern ALLEGRO_BITMAP* bitmap_pipe_top_left;
extern ALLEGRO_BITMAP* bitmap_pipe_top_right;
extern ALLEGRO_BITMAP* bitmap_pipe_left;
extern ALLEGRO_BITMAP* bitmap_pipe_right;
extern ALLEGRO_BITMAP* bitmap_cannon;
// ENEMIES
extern ALLEGRO_BITMAP* bitmap_enemy_goomba;
extern ALLEGRO_BITMAP* bitmap_enemy_koopa;
extern ALLEGRO_BITMAP* bitmap_plant;
// BACKGROUND
extern ALLEGRO_BITMAP* bitmap_cloud;
extern ALLEGRO_BITMAP* bitmap_cloud_big;
extern ALLEGRO_BITMAP* bitmap_bush;
extern ALLEGRO_BITMAP* bitmap_bush_big;
extern ALLEGRO_BITMAP* bitmap_fence;
    // HILL
    extern ALLEGRO_BITMAP* bitmap_hill_top;
    extern ALLEGRO_BITMAP* bitmap_hill_middle_patterned_right;
    extern ALLEGRO_BITMAP* bitmap_hill_middle_patterned_left;
    extern ALLEGRO_BITMAP* bitmap_hill_middle;
    extern ALLEGRO_BITMAP* bitmap_hill_slope_right;
    extern ALLEGRO_BITMAP* bitmap_hill_slope_left;
    // TREE
    extern ALLEGRO_BITMAP* bitmap_tree_bottom;
    extern ALLEGRO_BITMAP* bitmap_tree_small;
    extern ALLEGRO_BITMAP* bitmap_tree;
// END
extern ALLEGRO_BITMAP* bitmap_finish_flag;
// PLAYER
extern ALLEGRO_BITMAP* player_bitmap;
extern ALLEGRO_BITMAP* player_big_bitmap;

// loads textures
void init_bitmaps();

// destroys stuff
void destroy_bitmaps();

#endif
