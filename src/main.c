#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>

#include "defines.h"
#include "keyboard.h"
#include "object.h"
#include "list.h"
#include "player.h"
#include "object_updates.h"

int main()
{
    // initializing allegro
    if (!al_init())
    {
        return -2;
        system("echo failed to init Allegro >> log");
    }

    // creating the display etc.
    ALLEGRO_DISPLAY *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);

    // initializing the keyboard and image addon and checking if the initialization was successfull
    if (!al_install_keyboard())
    {
        al_show_native_message_box(display, "Error", "Error", "al_install_keyboard() failed!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    if (!al_init_image_addon())
    {
        al_show_native_message_box(display, "Error", "Error", "al_init_image_addon() failed!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    if (!al_init_primitives_addon())
    {
        al_show_native_message_box(display, "Error", "Error", "al_init_primitives_addon() failed!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // registering event sources
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // clearing the screen and starting the timer
    al_clear_to_color(LIGHT_BLUE);
    al_start_timer(timer);


    // creating structures
    Physics static_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Physics player_physics = create_physics(0.1f, 0.0f, 0.4f, 21, 1.0f);
    Physics goomba_physics = create_physics(3.0f, 0.0f, 3.0f, 20.0f, 1.0f);
    Physics koopa_physics  = create_physics(-3.0f, 0.0f, 3.0f, 20.0f, 1.0f);

    Object level[MAP_HEIGHT][MAP_WIDTH]; // row / column
    // the above array will only hold objects that are STATIC and unable to move so they always stay in their position in the grid
    Object background_elements[MAP_HEIGHT][MAP_WIDTH];
    // array that holds the decorative objects in the background

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int e = 0; e < MAP_WIDTH; e++)
        {
            init_object(&level[i][e], EMPTY, e*64, i*64, 64, 64, RECTANGLE, e*64, i*64, 64, 64, static_physics, 0);
            background_elements[i][e] = level[i][e];
        }
    }

    Object player;
    init_object(&player, PLAYER_BIG, 230 - 64, 6*64, 64, 64, RECTANGLE, 246, 6*64, 56, 64, player_physics, 15);

    ObjectsList non_static_elements;
    non_static_elements = create_objects_list(1);

    // bitmaps
    ALLEGRO_BITMAP* bitmap = al_create_bitmap(player.width, player.height * player.frames_number);
    bitmap = al_load_bitmap("./resources/mario_small.png");
    bind_bitmap(&player, bitmap);

    ALLEGRO_BITMAP* brick = al_create_bitmap(64, 64);
    ALLEGRO_BITMAP* brick2 = al_create_bitmap(64, 64);
    ALLEGRO_BITMAP* brick3 = al_create_bitmap(64, 64);
    ALLEGRO_BITMAP* secret_brick = al_create_bitmap(64, 64*2);
    ALLEGRO_BITMAP* cloud = al_create_bitmap(256, 256);
    ALLEGRO_BITMAP* enemy1 = al_create_bitmap(64, 64*2);
    ALLEGRO_BITMAP* enemy2 = al_create_bitmap(96, 80*5);

    brick = al_load_bitmap("./resources/brick_orange.png");
    brick2 = al_load_bitmap("./resources/brick_orange_unbreakable.png");
    brick3 = al_load_bitmap("./resources/orange_rock.png");
    secret_brick = al_load_bitmap("./resources/secret_brick.png");
    cloud = al_load_bitmap("./resources/cloud.png");
    enemy1 = al_load_bitmap("./resources/enemy_1.png");
    enemy2 = al_load_bitmap("./resources/enemy_2.png");

    Object temp_enemy;
        bind_bitmap(&temp_enemy, enemy1);
        init_object(&temp_enemy, ENEMY_GOOMBA, 260+64, 2*64, 64, 64, RECTANGLE, 260+64+7, 2*64+8, 50, 64-8, goomba_physics, 2);
        push_back_ol(&non_static_elements, temp_enemy);

        init_object(&temp_enemy, ENEMY_GOOMBA, 260, 2*64, 64, 64, RECTANGLE, 260+7, 2*64+8, 50, 64-8, goomba_physics, 2);
        push_back_ol(&non_static_elements, temp_enemy);

        init_object(&temp_enemy, ENEMY_GOOMBA, 20*64, 8*64, 64, 64, RECTANGLE, 20*64+7, 8*64+8, 50, 64-8, goomba_physics, 2);
        push_back_ol(&non_static_elements, temp_enemy);

        bind_bitmap(&temp_enemy, enemy2);
        init_object(&temp_enemy, ENEMY_KOOPA, 21*64, 8*64-16, 96, 80, RECTANGLE, 21*64+16, 8*64-16, 64, 80, koopa_physics, 4);
        push_back_ol(&non_static_elements, temp_enemy);

    Object temp_cloud;
        bind_bitmap(&temp_cloud, cloud);
        init_object(&temp_cloud, BACKGROUND, 4*64, 1*64, 256, 256, RECTANGLE, 0, 0, 1, 1, static_physics, 1);
        background_elements[1][4] = temp_cloud;

    Object temp_brick;
        bind_bitmap(&temp_brick, brick3);

        for (int i = 1; i < 9; i++)
        {
            init_object(&temp_brick, NORMAL_BLOCK, i*64, 8*64, 64, 64, RECTANGLE, i*64, 8*64, 64, 64, static_physics, 1);
            level[8][i] = temp_brick;
        }

        bind_bitmap(&temp_brick, brick);
        for (int i = 2; i < 8; i++)
        {
            if (i != 6)
            {
                init_object(&temp_brick, NORMAL_BLOCK, i*64, 5*64, 64, 64, RECTANGLE, i*64, 5*64, 64, 64, static_physics, 1);
                level[5][i] = temp_brick;
            }
            else
            {
                bind_bitmap(&temp_brick, secret_brick);
                init_object(&temp_brick, SECRET_BLOCK, i*64, 5*64, 64, 64, RECTANGLE, i*64, 5*64, 64, 64, static_physics, 2);
                level[5][i] = temp_brick;
                bind_bitmap(&temp_brick, brick);
            }
        }

        bind_bitmap(&temp_brick, brick3);
        for (int i = 6; i < 26; i++)
        {
            if (i != 15 && i != 25)
            {
                init_object(&temp_brick, NORMAL_BLOCK, i*64, 10*64, 64, 64, RECTANGLE, i*64, 10*64, 64, 64, static_physics, 1);
                level[10][i] = temp_brick;

            }
            else
            {
                bind_bitmap(&temp_brick, brick2);
                init_object(&temp_brick, UNBREAKABLE_BLOCK, i*64, 9*64, 64, 64, RECTANGLE, i*64, 9*64, 64, 64, static_physics, 1);
                level[9][i] = temp_brick;

                bind_bitmap(&temp_brick, brick2);
                init_object(&temp_brick, UNBREAKABLE_BLOCK, i*64, 8*64, 64, 64, RECTANGLE, i*64, 8*64, 64, 64, static_physics, 1);
                level[8][i] = temp_brick;

                bind_bitmap(&temp_brick, brick2);
                init_object(&temp_brick, UNBREAKABLE_BLOCK, i*64, 7*64, 64, 64, RECTANGLE, i*64, 7*64, 64, 64, static_physics, 1);
                level[7][i] = temp_brick;

                bind_bitmap(&temp_brick, brick3);
                init_object(&temp_brick, UNBREAKABLE_BLOCK, i*64, 10*64, 64, 64, RECTANGLE, i*64, 10*64, 64, 64, static_physics, 1);
                level[10][i] = temp_brick;
            }
        }


    // screen offset to the right
    int screen_offset = 0;

    // variable used to determine whether the screen should be redrawn(ed?)
    bool redraw = false;

    // arrays containing the states of keyboard buttons
    bool keys_active[KEYS_AMOUNT] = {false};
    bool keys_down[KEYS_AMOUNT]   = {false};
    bool keys_up[KEYS_AMOUNT]     = {false};

    // game's loop

    int frame = 0;

    while(true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        // if the timer has generated an event it's time to update the game's logics
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            frame++;
            if (frame > 60)
                frame = 0;

            update_non_static_objects(&non_static_elements, level, &player);
            animate_non_static_objects(&non_static_elements, frame, &player);
            update_player(&player, keys_active, keys_down, keys_up, level, &non_static_elements, frame);
            reset_buttons(keys_down, keys_up, KEYS_AMOUNT);
            animate_static_objects(level, frame, &player);

            if (player.hitbox.pos_x >= DISPLAY_WIDTH / 2)
            {
                screen_offset -= DISPLAY_WIDTH / 2 + screen_offset - player.hitbox.pos_x;
            }

            redraw = true;
        }
        // closing the window
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        // updating the keyboard

        update_buttons(&event, keys_down, keys_up, keys_active);

        // drawing things to the screen
        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            // BACKGROUND

            for (int height = 0; height < MAP_HEIGHT; height++) // TODO: limit the range to the window's size (also maybe merge background display with map display)
            {
                for (int width = 0; width < MAP_WIDTH; width++)
                {
                    if (background_elements[height][width].type != EMPTY)
                        draw_object(&background_elements[height][width], screen_offset / 2);
                }
            }

            // MAP

            for (int height = 0; height < MAP_HEIGHT; height++)
            {
                for (int width = 0; width < MAP_WIDTH; width++)
                {
                    if (level[height][width].type != EMPTY)
                        draw_object(&level[height][width], screen_offset);
                        //draw_hitbox(level[height][width].hitbox, screen_offset);
                }
            }

            // ACTORS

            for (int i = 0; i < non_static_elements.size; i++)
            {
                draw_object(get_element_pointer_ol(&non_static_elements, i), screen_offset);
                //draw_hitbox(get_element_pointer_ol(&non_static_elements, i)->hitbox, screen_offset);
            }

            // PLAYER

            draw_object(&player, screen_offset);
            //draw_hitbox(player.hitbox, screen_offset);

            al_flip_display();
            al_clear_to_color(LIGHT_BLUE);
        }
    }

    // cleanup
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(bitmap);
    al_destroy_bitmap(brick);
    delete_list(&non_static_elements);

    return 0;
}
