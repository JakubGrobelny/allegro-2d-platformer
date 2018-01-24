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
    Physics static_physics = create_physics(0, 0, 0   , 0    , 0);
    Physics player_physics = create_physics(0, 0, 1.2f, 20.0f, 1);
    Physics enemy_physics  = create_physics(0, 0, 2.0f, 0.0f , 0.4f);

    Object player;
    init_object(&player, PLAYER, 250, 250, 64, 64, RECTANGLE, 248, 250, 60, 64, player_physics, 15);

    ObjectsList obj_list;
    obj_list = create_objects_list(1);

    ObjectsList background_elements;
    background_elements = create_objects_list(1);

    ObjectsList enemies;
    enemies = create_objects_list(1);

    // bitmaps
    ALLEGRO_BITMAP* bitmap = al_create_bitmap(player.width, player.height * player.frames_number);
    bitmap = al_load_bitmap("./resources/mario_small.png");
    bind_bitmap(&player, bitmap);

    ALLEGRO_BITMAP* brick = al_create_bitmap(64, 64);
    brick = al_load_bitmap("./resources/brick_orange.png");

    ALLEGRO_BITMAP* brick2 = al_create_bitmap(64, 64);
    brick2 = al_load_bitmap("./resources/brick_orange_unbreakable.png");

    ALLEGRO_BITMAP* cloud = al_create_bitmap(256, 256);
    cloud = al_load_bitmap("./resources/cloud.png");

    ALLEGRO_BITMAP* enemy1 = al_create_bitmap(64, 64*2);
    enemy1 = al_load_bitmap("./resources/enemy_1.png");

    Object temp_enemy;

        bind_bitmap(&temp_enemy, enemy1);
        init_object(&temp_enemy, ENEMY_GOOMBA, 260+64, 520-4*64, 64, 64, RECTANGLE, 260+64, 520-4*64+8, 64, 64-8, enemy_physics, 2);
        temp_enemy.physics.speed.x = 4.0f;
        push_back_ol(&enemies, temp_enemy);

    Object temp_cloud;

        bind_bitmap(&temp_cloud, cloud);

        init_object(&temp_cloud, BACKGROUND, 130, 100, 128, 128, RECTANGLE, 130, 100, 256, 256, static_physics, 1);
        push_back_ol(&background_elements, temp_cloud);

        init_object(&temp_cloud, BACKGROUND, 620, 65, 128, 128, RECTANGLE, 620, 65, 256, 256, static_physics, 1);
        push_back_ol(&background_elements, temp_cloud);

    Object temp_brick;

        bind_bitmap(&temp_brick, brick);

        init_object(&temp_brick, PLATFORM, 260, 520, 64, 64, RECTANGLE, 260, 520, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64, 520, 64, 64, RECTANGLE, 260+64, 520, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*2, 520, 64, 64, RECTANGLE, 260+64*2, 520, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*3, 520, 64, 64, RECTANGLE, 260+64*3, 520, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*5, 520-3*64, 64, 64, RECTANGLE, 260+64*5, 520-3*64, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*6, 520-3*64, 64, 64, RECTANGLE, 260+64*6, 520-3*64, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64, 520-3*64, 64, 64, RECTANGLE, 260+64, 520-3*64, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+128, 520-3*64, 64, 64, RECTANGLE, 260+128, 520-3*64, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*8, 520-64, 64, 64, RECTANGLE, 260+64*8, 520-64, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*9, 520-64, 64, 64, RECTANGLE, 260+64*9, 520-64, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*10, 520-64, 64, 64, RECTANGLE, 260+64*10, 520-64, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*11, 520-64, 64, 64, RECTANGLE, 260+64*11, 520-64, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*12, 520-64, 64, 64, RECTANGLE, 260+64*12, 520-64, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*13, 520-64, 64, 64, RECTANGLE, 260+64*13, 520-64, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*12, 520-128, 64, 64, RECTANGLE, 260+64*12, 520-128, 64, 64, static_physics, 1);
        bind_bitmap(&temp_brick, brick2);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*12, 520-64*3, 64, 64, RECTANGLE, 260+64*12, 520-64*3, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);

        init_object(&temp_brick, PLATFORM, 260+64*12, 520-64*4, 64, 64, RECTANGLE, 260+64*12, 520-64*4, 64, 64, static_physics, 1);
        push_back_ol(&obj_list, temp_brick);


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

            update_non_static_objects(&enemies, &obj_list);
            update_player(&player, keys_active, keys_down, keys_up, &obj_list, &enemies, frame);
            reset_buttons(keys_down, keys_up, KEYS_AMOUNT);

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
            for (int i = 0; i < background_elements.size; i++)
            {
                draw_object(get_element_pointer_ol(&background_elements, i), 0); // TODO: add offset to SOME elements
            }

            // ACTORS
            draw_object(&player, screen_offset);

            for (int i = 0; i < enemies.size; i++)
            {
                draw_object(get_element_pointer_ol(&enemies, i), screen_offset);
            }

            // MAP
            for (int i = 0; i < obj_list.size; i++)
            {
                draw_object(get_element_pointer_ol(&obj_list, i), screen_offset);
            }

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
    delete_list(&obj_list);
    delete_list(&enemies);
    delete_list(&background_elements);

    return 0;
}
