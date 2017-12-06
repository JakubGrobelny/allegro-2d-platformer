#include <allegro5/allegro.h>
#include "defines.h"
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

    Player player = create_player(100, 100, 40, 20);

    while(true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        // aktualizujemy stan tylko co 1/60 sekundy
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
        }

        // wylaczanie gdy nacisniety zostanie klawisz escape lub gdy okno zostanie zamkniete
        if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
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
