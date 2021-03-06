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
#include "editor.h"

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
    LevelList* level_list = init_level_list();
    LevelList* current_level = level_list;

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
    init_object(&player, PLAYER, START_X, START_Y, 64, 64, RECTANGLE, 0, 0, 56, 64, player_physics, 15);
    bind_bitmap(&player, player_bitmap);

    ObjectsList non_static_elements = create_objects_list(1);
    ObjectsList clouds = create_objects_list(1);


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
    int level_status = 0; // 1 - reload, 2 - next level, 3 - game over, -1 - finished the game

    main_menu(event_queue, &exit, &mode_editor, keys_active, keys_down, keys_up);

    Object editor_obj;
    editor_obj.type = EMPTY;

    if (mode_editor)
        current_level = select_level(level_list, event_queue, keys_active, keys_down, keys_up);

    load_level(current_level->path, level, background_elements, &non_static_elements, &clouds);

    while(!exit)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        al_get_mouse_state(&mouse_state);

        // if the timer has generated an event it's time to update the game's logics
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            if (!menu && !mode_editor)
            {
                frame++;

                if (frame > 60)
                    frame = 0;

                update_non_static_objects(&non_static_elements, level, &player);
                animate_non_static_objects(&non_static_elements, frame, &player);
                update_player(&player, keys_active, keys_down, keys_up, level, &non_static_elements, frame, &level_status);
                animate_static_objects(level, frame, &player, &non_static_elements);

                if (player.hitbox.pos_x >= DISPLAY_WIDTH / 2)
                    screen_offset -= DISPLAY_WIDTH / 2 + screen_offset - player.hitbox.pos_x;
                else
                    screen_offset = 0;

                // restart/next level/game over
                if (level_status == 1)
                {
                    load_level(current_level->path, level, background_elements, &non_static_elements, &clouds);
                    level_status = 0;
                }
                else if (level_status == 2)
                {
                    if (current_level->next != NULL)
                    {
                        if (player.counter == 1)
                        {
                            current_level = current_level->next;
                            respawn_player(&player, START_X, START_Y);
                            load_level(current_level->path, level, background_elements, &non_static_elements, &clouds);
                            level_status = 0;
                        }
                    }
                    else
                    {
                        level_status = -1;
                    }
                }
                else if (level_status == 3)
                {
                    if (player.counter == 1)
                    {
                        player.alive = true;
                        current_level = level_list;
                        load_level(current_level->path, level, background_elements, &non_static_elements, &clouds);
                        level_status = 0;
                        respawn_player(&player, START_X, START_Y);
                        lives = 3;
                    }
                }
            }
            else if (menu && !mode_editor)
                update_pause_menu(&menu, &exit, keys_active, keys_down, keys_up);
            else if (menu && mode_editor)
                update_editor_pause_menu(&menu, &exit, keys_active, keys_down, current_level, level, background_elements, &non_static_elements);
            else if (mode_editor)
            {
                screen_offset += move_screen(keys_down, keys_up, keys_active);

                if (screen_offset < 0)
                    screen_offset = 0;
                if (screen_offset > (MAP_WIDTH-1) * 64)
                    screen_offset = (MAP_WIDTH-1) * 64;

                update_editor(&editor_obj, keys_down, keys_up, keys_active, level, background_elements, &non_static_elements, screen_offset);
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
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER && level_status == -1)
            exit = true;

        // updating the keyboard
        update_buttons(&event, keys_down, keys_up, keys_active);

        // drawing things to the screen
        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            // CLOUDS

            for (int i = 0; i < clouds.size; i++)
            {
                if (distance_x(&player, get_element_pointer_ol(&clouds, i)) <= RENDER_DISTANCE + screen_offset / 2 || mode_editor)
                    draw_object(get_element_pointer_ol(&clouds, i), (int)(screen_offset / 2));
            }

            // BACKGROUND

            for (int height = 0; height < MAP_HEIGHT; height++) // TODO: limit the range to the window's size (also maybe merge background display with map display)
            {
                for (int width = 0; width < MAP_WIDTH; width++)
                {
                    if (distance_x(&player, &level[height][width]) <= RENDER_DISTANCE || mode_editor)
                        if (background_elements[height][width].type != EMPTY)
                            draw_object(&background_elements[height][width], screen_offset);
                }
            }

            // MAP

            for (int height = 0; height < MAP_HEIGHT; height++)
            {
                for (int width = 0; width < MAP_WIDTH; width++)
                {
                    if (level[height][width].type != EMPTY)
                    {
                        if (distance_x(&player, &level[height][width]) <= RENDER_DISTANCE || mode_editor)
                            draw_object(&level[height][width], screen_offset);
                        //draw_hitbox(level[height][width].hitbox, screen_offset);
                    }
                }
            }

            // ACTORS

            for (int i = 0; i < non_static_elements.size; i++)
            {
                if (distance_x(&player, get_element_pointer_ol(&non_static_elements, i)) <= RENDER_DISTANCE || mode_editor)
                    draw_object(get_element_pointer_ol(&non_static_elements, i), screen_offset);
                //draw_hitbox(get_element_pointer_ol(&non_static_elements, i)->hitbox, screen_offset);
            }

            // PLAYER

            draw_object(&player, screen_offset);
            //draw_hitbox(player.hitbox, screen_offset);
            if (!mode_editor)
                draw_hud(lives, coins);

            if (!player.alive && level_status == 3)
                draw_game_over_screen();
            else if (player.alive && level_status == 2)
                draw_next_level_screen(current_level->next->path);
            else if (level_status == -1)
                draw_congratulations_screen();

            if (menu && !mode_editor)
                draw_pause_menu();
            else if (menu)
                draw_editor_pause_menu();

            if (mode_editor && !menu)
            {
                draw_grid(screen_offset);
                if (editor_obj.type != EMPTY)
                    draw_object(&editor_obj, screen_offset);
                draw_editor_hud(selected_layer, selected_object, editor_obj.pos_x / 64, editor_obj.pos_y / 64);
            }

            al_flip_display();
            al_clear_to_color(LIGHT_BLUE);
        }
    }

    // cleanup
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    destroy_bitmaps();
    delete_level_list(level_list);

    return 0;
}
