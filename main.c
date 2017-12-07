#include <allegro5/allegro.h>
#include "defines.h"
#include "keyboard.h"
#include "object.h"
#include "list.h"

int main()
{
    // inicjalizacja allegro TODO: sprawdzanie czy udalo sie utworzyc display itd.
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    ALLEGRO_DISPLAY *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_clear_to_color(WHITE);
    al_start_timer(timer);

    bool redraw = false;
    bool key[4] = {false}; // tablica przechowujaca stan klawisza (true - wcisniety)

    Object player = create_object(230, 150, 40, 40, generate_static_physics(), 1);
    Object platform = create_object(100, 400, 200, 50, generate_static_physics(), 0);

    while(true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            update_player(&player, key); // TODO: przekazywac liste objektow do update_player i sprawdzac kolizje przed przemieszczeniem

            if (collide(player.hitbox, platform.hitbox, 1))
            {
                player.pos_y = platform.pos_y - player.height; // TEST
            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            draw_object(&player);
            draw_object(&platform);
            al_flip_display();
            al_clear_to_color(WHITE);
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
