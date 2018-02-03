#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>

#include "defines.h"
#include "keyboard.h"
#include "object.h"
#include "list.h"
#include "player.h"
#include "object_updates.h"
#include "interface.h"
#include "bitmap.h"
#include "level.h"

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
    if (!al_install_mouse())
    {
        al_show_native_message_box(display, "Error", "Error", "al_install_mouse() failed!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
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
    if (!al_init_font_addon())
    {
        al_show_native_message_box(display, "Error", "Error", "al_init_font_addon() failed!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    if (!al_init_ttf_addon())
    {
        al_show_native_message_box(display, "Error", "Error", "al_init_ttf_addon() failed!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;

    }

    init_interface();
    init_bitmaps();

    // registering event sources
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // clearing the screen and starting the timer
    al_clear_to_color(LIGHT_BLUE);
    al_start_timer(timer);

    // creating structures

    Object level[MAP_HEIGHT][MAP_WIDTH]; // row / column
    // the above array will only hold objects that are STATIC and unable to move so they always stay in their position in the grid
    Object background_elements[MAP_HEIGHT][MAP_WIDTH];
    // array that holds the decorative objects in the background

    Object player;
    Physics player_physics = create_physics(0.1f, 0.0f, 0.47f, 21, 0.9f);
    init_object(&player, PLAYER, 230 - 64, 6*64, 64, 64, RECTANGLE, 246, 6*64, 56, 64, player_physics, 15);

    ObjectsList non_static_elements = create_objects_list(1);
    ObjectsList clouds = create_objects_list(1);

    load_level("./level/test_level.lvl", level, background_elements, &non_static_elements, &clouds);

    // bitmaps
    player_bitmap = al_create_bitmap(player.width, player.height * player.frames_number);
    player_bitmap = al_load_bitmap("./resources/textures/mario_small.png");
    player_big_bitmap = al_create_bitmap(64, 128 * 17);
    player_big_bitmap = al_load_bitmap("./resources/textures/mario_big.png");
    bind_bitmap(&player, player_bitmap);

    // Object temp_cloud; // TODO change to objectslist clouds
    //     bind_bitmap(&temp_cloud, cloud);
    //     init_object(&temp_cloud, BACKGROUND, 4*64, 1*64, 256, 256, RECTANGLE, 0, 0, 1, 1, static_physics, 1);
    //     background_elements[1][4] = temp_cloud;

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
    bool menu = false;
    bool exit = false;
    bool mode_editor = false;

    main_menu(event_queue, &exit, &mode_editor, keys_active, keys_down, keys_up);
    //load_level();

    while(!exit)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        al_get_mouse_state(&mouse_state);

        // if the timer has generated an event it's time to update the game's logics
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            if (!menu)
            {
                frame++;
                if (frame > 60)
                frame = 0;

                update_non_static_objects(&non_static_elements, level, &player);
                animate_non_static_objects(&non_static_elements, frame, &player);
                update_player(&player, keys_active, keys_down, keys_up, level, &non_static_elements, frame);
                animate_static_objects(level, frame, &player, &non_static_elements);

                if (player.hitbox.pos_x >= DISPLAY_WIDTH / 2)
                    screen_offset -= DISPLAY_WIDTH / 2 + screen_offset - player.hitbox.pos_x;
                else
                    screen_offset = 0;
            }
            else
            {
                update_pause_menu(&menu, &exit, keys_active, keys_down, keys_up);
            }

            reset_buttons(keys_down, keys_up, KEYS_AMOUNT);
            redraw = true;
        }
        // closing the window
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            if (menu)
                menu = false;
            else
                menu = true;
        }

        // updating the keyboard

        update_buttons(&event, keys_down, keys_up, keys_active);

        // drawing things to the screen
        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            // BACKGROUND

            // for (int height = 0; height < MAP_HEIGHT; height++) // TODO: limit the range to the window's size (also maybe merge background display with map display)
            // {
            //     for (int width = 0; width < MAP_WIDTH; width++)
            //     {
            //         if (background_elements[height][width].type != EMPTY)
            //             draw_object(&background_elements[height][width], screen_offset / 2);
            //     }
            // }

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
            draw_hud(lives, coins);

            if (menu)
                draw_pause_menu();

            al_flip_display();
            al_clear_to_color(LIGHT_BLUE);
        }
    }

    // cleanup
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    destroy_bitmaps();

    return 0;
}
