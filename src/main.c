#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>

#include "defines.h"
#include "keyboard.h"
#include "object.h"
#include "list.h"
#include "player.h"

int main()
{
    if (!al_init())
    {
        return -2;
        system("echo failed to init Allegro >> log");
    }

    ALLEGRO_DISPLAY *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
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

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_clear_to_color(WHITE);
    al_start_timer(timer);

    Object player;
    init_object(&player, 250, 250, 64, 64, rectangle, generate_static_physics(), 2);

    ObjectsList obj_list;
    obj_list = create_objects_list(1);

    // BITMAPS
    ALLEGRO_BITMAP* bitmap = al_create_bitmap(player.width, player.height * player.frames_number);
    bitmap = al_load_bitmap("./resources/test.png");
    bind_bitmap(&player, bitmap);

    ALLEGRO_BITMAP* platform = al_create_bitmap(128, 32);
    platform = al_load_bitmap("./resources/platform.png");

    Object temp_platform;
    bind_bitmap(&temp_platform, platform);

    for (int i = 0; i < 5; i++)
    {
        init_object(&temp_platform, 120 * (i+1), 450 + 50 * i, 128, 32, rectangle, generate_static_physics(), 1);
        push_back_ol(&obj_list, temp_platform);
    }

    bool redraw = false;
    bool keys_active[KEYS_AMOUNT] = {false};
    bool keys_down[KEYS_AMOUNT]   = {false};
    bool keys_up[KEYS_AMOUNT]     = {false};

    while(true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            update_player(&player, keys_active, keys_down, keys_up, &obj_list);
            reset_buttons(keys_down, keys_up, KEYS_AMOUNT);
            redraw = true;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        update_buttons(&event, keys_down, keys_up, keys_active);

        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            for (int i = 0; i < 5; i++)
            {
                draw_object(get_element_pointer_ol(&obj_list, i));
            }

            draw_object(&player);
            al_flip_display();
            al_clear_to_color(WHITE);
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(bitmap);
    al_destroy_bitmap(platform);
    delete_list(&obj_list);

    return 0;
}
