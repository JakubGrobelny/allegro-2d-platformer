#include <allegro5/allegro.h>
#include "defines.h"
#include "keyboard.h"
#include "object.h"
#include "list.h"
#include "player.h"
#include <stdio.h>

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
    bool key[5] = {false}; // tablica przechowujaca stan klawisza (true - wcisniety)

    Object player = create_object(230, 150, 40, 40, generate_static_physics(), 1);

    ObjectsList obj_list = create_objects_list(3);

    // TESTY LISTY OBIEKTOW, PUSH_BACK is POP_ELEMENT CHYBA DZIALAJA // DZIALA :DDD
    push_back_ol(&obj_list, create_object(330, 200, 40, 40, generate_static_physics(), 0));
    push_back_ol(&obj_list, create_object(900, 200, 40, 40, generate_static_physics(), 0));
    push_back_ol(&obj_list, create_object(600, 600, 40, 40, generate_static_physics(), 0));
    push_back_ol(&obj_list, create_object(390, 100, 40, 40, generate_static_physics(), 0));
    push_back_ol(&obj_list, create_object(100, 400, 200, 50, generate_static_physics(), 0));
    push_back_ol(&obj_list, create_object(300, 250, 100, 25, generate_static_physics(), 0));
    push_back_ol(&obj_list, create_object(800, 500, 40, 40, generate_static_physics(), 1));
    push_back_ol(&obj_list, create_object(770, 650, 40, 40, generate_static_physics(), 1));
    push_back_ol(&obj_list, create_object(100, 400, 200, 50, generate_static_physics(), 0));
    push_back_ol(&obj_list, create_object(300, 250, 100, 25, generate_static_physics(), 0));
    push_back_ol(&obj_list, create_object(800, 500, 40, 40, generate_static_physics(), 1));
    push_back_ol(&obj_list, create_object(770, 650, 40, 40, generate_static_physics(), 1));
    bool popped = false; //TEST
    //#########################################################################################

    while(true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            update_player(&player, key, &obj_list); // TODO: przekazywac liste objektow do update_player i sprawdzac kolizje przed przemieszczeniem
            if (key[KEY_ENTER] && !popped)
            {
                popped = true;

                int e = obj_list.size;
                for (int i = 0; i < e; i++)
                {
                    pop_first_ol(&obj_list);
                }
            }
            //if (collide(player.hitbox, platform.hitbox, 1))
            //{
        //        player.pos_y = platform.pos_y - player.height; // TEST
        //    }
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
                case ALLEGRO_KEY_ENTER:
                    key[KEY_ENTER] = true;
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
                case ALLEGRO_KEY_ENTER:
                    key[KEY_ENTER] = false;
                    break;
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            draw_object(player);

            for(int i = 0; i < obj_list.size; i++)
            {
                draw_object(get_element_ol(&obj_list, i));
            }

            al_flip_display();
            al_clear_to_color(WHITE);
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
