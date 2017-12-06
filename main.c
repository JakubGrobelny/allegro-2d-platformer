#include <allegro5/allegro.h>
#include "defines.h"
#include "keyboard.h"
#include "player.h"

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

    al_clear_to_color(al_map_rgba(255, 255, 255, 0));
    al_start_timer(timer);

    bool redraw = false;
    bool key[4] = {false}; // tablica przechowujaca stan klawisza (true - wcisniety)

    Player player = create_player(230, 150, 40, 80, 5);

    while(true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        // aktualizujemy stan tylko co 1/60 sekundy
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            update_player(&player, key);
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            // wylaczanie gdy nacisniety zostanie klawisz escape lub gdy okno zostanie zamkniete
            break;
        }
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
            draw_player(&player);
            al_flip_display();
            al_clear_to_color(al_map_rgba(255, 255, 255, 0));
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
