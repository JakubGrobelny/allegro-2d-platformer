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

    // registering event sources
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // clearing the screen and starting the timer
    al_clear_to_color(LIGHT_BLUE);
    al_start_timer(timer);

    // creating structures
    Physics static_physics = create_physics(0, 0, 0, 0, 0);
    Physics player_physics = create_physics(0, 0, 1.2f, 20.0f, 1);

    Object player;
    init_object(&player, PLAYER, 250, 250, 64, 64, RECTANGLE, 242, 250, 48, 64, player_physics, 15);

    ObjectsList obj_list;
    obj_list = create_objects_list(1);

    // bitmaps
    ALLEGRO_BITMAP* bitmap = al_create_bitmap(player.width, player.height * player.frames_number);
    bitmap = al_load_bitmap("./resources/mario_small.png");
    bind_bitmap(&player, bitmap);

    ALLEGRO_BITMAP* platform = al_create_bitmap(128, 32);
    platform = al_load_bitmap("./resources/platform.png");

    Object temp_platform;
    init_object(&temp_platform, PLATFORM, 260, 520, 128, 32, RECTANGLE, 260, 520, 128, 32, static_physics, 1);
    bind_bitmap(&temp_platform, platform);
    push_back_ol(&obj_list, temp_platform);

    init_object(&temp_platform, PLATFORM, 260 + 128, 520, 128, 32, RECTANGLE, 260 + 128, 520, 128, 32, static_physics, 1);
    push_back_ol(&obj_list, temp_platform);

    init_object(&temp_platform, PLATFORM, 260 + 128, 520 - 140, 128, 32, RECTANGLE, 260 + 128, 520 - 140, 128, 32, static_physics, 1);
    push_back_ol(&obj_list, temp_platform);

    // variable used to determine whether the screen should be redrawed
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

            update_player(&player, keys_active, keys_down, keys_up, &obj_list, frame);
            reset_buttons(keys_down, keys_up, KEYS_AMOUNT);
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

            draw_object(&player);

            for (int i = 0; i < obj_list.size; i++)
            {
                draw_object(get_element_pointer_ol(&obj_list, i));
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
    al_destroy_bitmap(platform);
    delete_list(&obj_list);

    return 0;
}
