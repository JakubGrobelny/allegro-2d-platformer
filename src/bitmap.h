#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#ifndef _BITMAP
#define _BITMAP

extern ALLEGRO_BITMAP* bitmap_brick;
extern ALLEGRO_BITMAP* bitmap_brick_unbreakable;
extern ALLEGRO_BITMAP* bitmap_brick_floor;
extern ALLEGRO_BITMAP* bitmap_secret_brick;
extern ALLEGRO_BITMAP* bitmap_cloud;
extern ALLEGRO_BITMAP* bitmap_enemy_goomba;
extern ALLEGRO_BITMAP* bitmap_enemy_koopa;
extern ALLEGRO_BITMAP* bitmap_plant;
extern ALLEGRO_BITMAP* bitmap_pipe_top_left;
extern ALLEGRO_BITMAP* bitmap_pipe_top_right;
extern ALLEGRO_BITMAP* bitmap_pipe_left;
extern ALLEGRO_BITMAP* bitmap_pipe_right;
extern ALLEGRO_BITMAP* bitmap_cannon;

extern ALLEGRO_BITMAP* player_bitmap;

// loads textures
void init_bitmaps();

// destroys stuff
void destroy_bitmaps();

#endif
