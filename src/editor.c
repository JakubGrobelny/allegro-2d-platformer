#include "editor.h"

int selected_object = 0;
int selected_layer = MAP_LAYER; // 0 - map, 1 - background, 2 - objects
const int layer_max_object[3] = {12, 11, 4}; // amount of possible object types on every layer

LevelList* select_level(LevelList* level_list, ALLEGRO_EVENT_QUEUE* event_queue,  bool* keys_active, bool* keys_down, bool* keys_up)
{
    bool selected = false;
    char file_name[40] = "./level/";
    int i = 8;
    bool redraw = false;

    while (!selected)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        update_buttons(&event, keys_down, keys_up, keys_active);

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            if (i < 39)
            {
                if (keys_down[KEY_DOT])
                {
                    file_name[i] = '.';
                    i++;
                }
                else
                {
                    for (int key = KEY_A; key <= KEY_Z; key++)
                    {
                        if (keys_down[key])
                        {
                            if (keys_active[KEY_RSHIFT])
                                file_name[i] = 'A' + key;
                            else
                                file_name[i] = 'a' + key;
                            i++;
                            break;
                        }
                    }
                }
            }

            if (i > 8)
            {
                if (keys_down[KEY_BACKSPACE])
                {
                    file_name[i - 1] = '\0';
                    i--;
                }
            }

            if (i > 8 && keys_down[KEY_ENTER])
                selected = true;

            reset_buttons(keys_down, keys_up, KEYS_AMOUNT);
        }

        if (redraw)
        {
            al_draw_filled_rectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, BLACK);
            draw_text(DISPLAY_WIDTH / 2, 32, ALIGNMENT_CENTRE, "Enter the file name:");
            draw_text(DISPLAY_WIDTH / 2, 128, ALIGNMENT_CENTRE, file_name);
            redraw = false;

            al_flip_display();
        }
    }

    LevelList* pointer = level_list;
    LevelList* previous;

    while(pointer)
    {
        if (compare_strings(pointer->path, file_name))
            break;

        if (pointer->next == NULL)
            previous = pointer;

        pointer = pointer->next;
    }

    if (!pointer)
    {
        FILE* file;

        file = fopen("./level/level_index", "a");
        fprintf(file, "%s\n", file_name);

        fclose(file);

        file = fopen(file_name, "w");

        for (int y = 0; y < MAP_HEIGHT*2; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                if(y != 10)
                    fprintf(file, "0");
                else
                    fprintf(file, "@");
            }
            fprintf(file, "\n");
        }

        fclose(file);

        pointer = create_list_element(file_name, previous);
        previous->next = pointer;

        return pointer;
    }
    else
        return pointer;
}

int move_screen(bool* keys_down, bool* keys_up, bool* keys_active)
{
    int multiplier = 1;
    if (keys_active[KEY_SHIFT])
        multiplier = 2;

    if (keys_active[KEY_LEFT])
        return -16 * multiplier;
    else if (keys_active[KEY_RIGHT])
        return 16 * multiplier;
    return 0;
}

void update_editor(Object* editor_obj, bool* keys_down, bool* keys_up, bool* keys_active, Object level[MAP_HEIGHT][MAP_WIDTH], Object background[MAP_HEIGHT][MAP_WIDTH], ObjectsList* objects, int screen_offset)
{
    if (keys_down[KEY_1])
        selected_layer = MAP_LAYER;
    else if (keys_down[KEY_2])
        selected_layer = BACKGROUND_LAYER;
    else if (keys_down[KEY_3])
        selected_layer = OBJECT_LAYER;

    if (keys_down[KEY_A] || keys_down[KEY_DOWN])
        selected_object--;
    else if (keys_down[KEY_D] || keys_down[KEY_UP])
        selected_object++;

    if (selected_object > layer_max_object[selected_layer])
        selected_object = 0;
    else if (selected_object < 0)
        selected_object = layer_max_object[selected_layer];

    select_object(editor_obj, (mouse_state.x + screen_offset) / 64, (mouse_state.y) / 64);

    // mouse click:
}

Object* select_object(Object* editor_obj, int pos_x, int pos_y)
{
    if (pos_x < 0)
        pos_x = 0;
    if (pos_y < 0)
        pos_y = 0;
    if (pos_x >= MAP_WIDTH)
        pos_x = MAP_WIDTH;
    if (pos_y >= MAP_HEIGHT)
        pos_y = MAP_HEIGHT;

    // snapping to grid
    pos_x *= 64;
    pos_y *= 64;

    editor_obj->animation_frame = 0;

    //epic nested switch-case
    switch (selected_layer)
    {
        case MAP_LAYER:
        {
            Physics static_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
            switch (selected_object)
            {
                case 0: // empty
                    init_object(editor_obj, EMPTY, pos_x, pos_y, 64, 64, RECTANGLE, 0, 0, 64, 64, static_physics, 0);
                    break;
                case 1: // brick
                    bind_bitmap(editor_obj, bitmap_brick);
                    init_object(editor_obj, NORMAL_BLOCK, pos_x, pos_y, 64, 64, RECTANGLE, pos_x, pos_y, 64, 64, static_physics, 1);
                    break;
                case 2: // stone
                    bind_bitmap(editor_obj, bitmap_brick_floor);
                    init_object(editor_obj, NORMAL_BLOCK, pos_x, pos_y, 64, 64, RECTANGLE, pos_x, pos_y, 64, 64, static_physics, 1);
                    break;
                case 3: // secret coin x 1
                    bind_bitmap(editor_obj, bitmap_secret_brick);
                    init_object(editor_obj, SECRET_BLOCK, pos_x, pos_y, 64, 64, RECTANGLE, pos_x, pos_y, 64, 64, static_physics, 2);
                    editor_obj->physics.mass = 1.0f;
                    break;
                case 4: // secret mushroom
                    bind_bitmap(editor_obj, bitmap_secret_brick);
                    init_object(editor_obj, SECRET_BLOCK_MUSHROOM, pos_x, pos_y, 64, 64, RECTANGLE, pos_x, pos_y, 64, 64, static_physics, 2);
                    break;
                case 5: // secret coin x 5
                    bind_bitmap(editor_obj, bitmap_secret_brick);
                    init_object(editor_obj, SECRET_BLOCK, pos_x, pos_y, 64, 64, RECTANGLE, pos_x, pos_y, 64, 64, static_physics, 2);
                    editor_obj->physics.mass = 5.0f;
                    break;
                case 6: // cannon right
                    bind_bitmap(editor_obj, bitmap_cannon);
                    init_object(editor_obj, CANNON_RIGHT, pos_x, pos_y, 64, 128, RECTANGLE, pos_x, pos_y, 64, 128, static_physics, 1);
                    break;
                case 7: // cannon left
                    bind_bitmap(editor_obj, bitmap_cannon);
                    init_object(editor_obj, CANNON_RIGHT, pos_x, pos_y, 64, 128, RECTANGLE, pos_x, pos_y, 64, 128, static_physics, 1);
                    break;
                case 8: // unbreakable brick
                    bind_bitmap(editor_obj, bitmap_brick_unbreakable);
                    init_object(editor_obj, UNBREAKABLE_BLOCK, pos_x, pos_y, 64, 64, RECTANGLE, pos_x, pos_y, 64, 64, static_physics, 1);
                    break;
                case 9: // pipe top left
                    bind_bitmap(editor_obj, bitmap_pipe_top_left);
                    init_object(editor_obj, UNBREAKABLE_BLOCK, pos_x, pos_y, 64, 64, RECTANGLE, pos_x, pos_y, 64, 64, static_physics, 1);
                    break;
                case 10: // pipe top right
                    bind_bitmap(editor_obj, bitmap_pipe_top_right);
                    init_object(editor_obj, UNBREAKABLE_BLOCK, pos_x, pos_y, 64, 64, RECTANGLE, pos_x, pos_y, 64, 64, static_physics, 1);
                    break;
                case 11: // pipe bottom right
                    bind_bitmap(editor_obj, bitmap_pipe_right);
                    init_object(editor_obj, UNBREAKABLE_BLOCK, pos_x, pos_y, 64, 64, RECTANGLE, pos_x, pos_y, 64, 64, static_physics, 1);
                    break;
                case 12: // pipe bottom left
                    bind_bitmap(editor_obj, bitmap_pipe_left);
                    init_object(editor_obj, UNBREAKABLE_BLOCK, pos_x, pos_y, 64, 64, RECTANGLE, pos_x, pos_y, 64, 64, static_physics, 1);
                    break;
            }
            break;
        }
        case BACKGROUND_LAYER:
        {
            Physics static_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
            init_object(editor_obj, BACKGROUND, pos_x, pos_y, 64, 64, RECTANGLE, pos_x, pos_y, 0, 0, static_physics, 1);
            switch (selected_object)
            {
                case 0: // bush
                    bind_bitmap(editor_obj, bitmap_bush);
                    editor_obj->width = 128;
                    break;
                case 1: // bush big
                    bind_bitmap(editor_obj, bitmap_bush_big);
                    editor_obj->width= 192;
                    editor_obj->height = 68;
                    break;
                case 2: // fence
                    bind_bitmap(editor_obj, bitmap_fence);
                    break;
                case 3: // hill top
                    bind_bitmap(editor_obj, bitmap_hill_top);
                    break;
                case 4: // hill middle pattern right
                    bind_bitmap(editor_obj, bitmap_hill_middle_patterned_left);
                    break;
                case 5: // hill middle patern left
                    bind_bitmap(editor_obj, bitmap_hill_middle_patterned_left);
                    break;
                case 6: // hill middle
                    bind_bitmap(editor_obj, bitmap_hill_middle);
                    break;
                case 7: // hill slope right
                    bind_bitmap(editor_obj, bitmap_hill_slope_right);
                    break;
                case 8: // hill slope left
                    bind_bitmap(editor_obj, bitmap_hill_slope_left);
                    break;
                case 9: // tree bottom
                    bind_bitmap(editor_obj, bitmap_tree_bottom);
                    break;
                case 10: // tree small
                    bind_bitmap(editor_obj, bitmap_tree_small);
                    break;
                case 11: // tree
                    bind_bitmap(editor_obj, bitmap_tree);
                    editor_obj->height = 128;
                    break;
            }
            break;
        }
        case OBJECT_LAYER:
        {
            switch (selected_object)
            {
                case 0: // goomba
                    bind_bitmap(editor_obj, bitmap_enemy_goomba);
                    Physics goomba_physics = create_physics(3.0f, 0.0f, 3.0f, 20.0f, 1.0f);
                    init_object(editor_obj, ENEMY_GOOMBA, pos_x, pos_y, 64, 64, RECTANGLE, pos_x + 7, pos_y + 8, 50, 56, goomba_physics, 2);
                    break;
                case 1: // koopa
                    bind_bitmap(editor_obj, bitmap_enemy_koopa);
                    Physics koopa_physics  = create_physics(-3.0f, 0.0f, 3.0f, 20.0f, 2.0f);
                    init_object(editor_obj, ENEMY_KOOPA, pos_x, pos_y, 96, 80, RECTANGLE, pos_x + 16, pos_y - 16, 64, 80, koopa_physics, 4);
                    editor_obj->animation_frame = 5;
                    break;
                case 2: // flying koopa
                    bind_bitmap(editor_obj, bitmap_enemy_koopa);
                    Physics flying_koopa_physics = create_physics(-3.0f, 0.0f, 3.0f, 13.0f, 0.5f);
                    init_object(editor_obj, ENEMY_KOOPA_FLYING, pos_x, pos_y, 96, 80, RECTANGLE, pos_x + 16, pos_y - 16, 64, 80, flying_koopa_physics, 4);
                    editor_obj->animation_frame = 2;
                    break;
                case 3: // piranha plant
                    bind_bitmap(editor_obj, bitmap_plant);
                    Physics piranha_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                    init_object(editor_obj, ENEMY_PIRANHA_PLANT, pos_x, pos_y, 128, 128, RECTANGLE, pos_x + 32, pos_y + 48, 64, 80, piranha_physics, 4);
                    editor_obj->animation_frame = 2;
                    break;
                case 4: // coin
                    bind_bitmap(editor_obj, bitmap_secret_brick);
                    Physics coin_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                    init_object(editor_obj, COIN, pos_x, pos_y, 64, 64, RECTANGLE, pos_x + 21, pos_y, 24, 64, coin_physics, 1);
                    editor_obj->animation_frame = 3;
                    editor_obj->alive = false;
                    break;
            }
            break;
        }
    }
}
