#include "level.h"

LevelList* init_level_list()
{
    FILE* level_index;
    level_index = fopen("./level/level_index", "r");

    char temp_path[256];

    LevelList* list = malloc(sizeof(LevelList));
    list->next = NULL;
    list->previous = NULL;
    fgets(temp_path, 256, level_index);

    int len = strlen(temp_path);
    if (len > 0 && temp_path[len-1] == '\n')
        temp_path[len-1] = '\0';
    strncpy(list->path, temp_path, 256);

    LevelList* pointer = list;

    while(fgets(temp_path, 256, level_index))
    {
        len = strlen(temp_path);
        if (len > 0 && temp_path[len-1] == '\n')
            temp_path[len-1] = '\0';

        pointer->next = create_list_element(temp_path, pointer);
        pointer = pointer->next;
    }

    fclose(level_index);

    return list;
}

LevelList* create_list_element(char path[], LevelList* previous)
{
    LevelList* element = malloc(sizeof(LevelList));
    element->previous = previous;
    element->next = NULL;
    strncpy(element->path, path, 256);
    return element;
}

void delete_level_list(LevelList* list)
{
    while (list->next != NULL)
    {
        list = list->next;
        free(list->previous);
    }

    free(list);
}

void save_level(LevelList* current_level, Object level[MAP_HEIGHT][MAP_WIDTH], Object background[MAP_HEIGHT][MAP_WIDTH], ObjectsList* non_static_elements)
{
    FILE* level_file;
    level_file = fopen(current_level->path, "w");

    // saving map

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            Object* obj = &level[y][x];

            char output = '0';

            switch (obj->type)
            {
                case NORMAL_BLOCK:
                {
                    if (obj->bitmap == bitmap_brick)
                        output = '#';
                    else if (obj->bitmap == bitmap_brick_floor)
                        output = '@';
                    break;
                }
                case SECRET_BLOCK:
                {
                    if (obj->physics.mass >= 5.0f)
                        output = '5';
                    else
                        output = '$';
                    break;
                }
                case SECRET_BLOCK_MUSHROOM:
                    output = '&';
                    break;
                case CANNON_LEFT:
                    output = '<';
                    break;
                case CANNON_RIGHT:
                    output = '>';
                    break;
                case UNBREAKABLE_BLOCK:
                {
                    if (obj->bitmap == bitmap_brick_unbreakable)
                        output = '!';
                    else if (obj->bitmap == bitmap_pipe_top_left)
                        output = 'L';
                    else if (obj->bitmap == bitmap_pipe_left)
                        output = 'l';
                    else if (obj->bitmap == bitmap_pipe_right)
                        output = 'r';
                    else if (obj->bitmap == bitmap_pipe_top_right)
                        output = 'R';
                    break;
                }
                default:
                    break;
            }

            fprintf(level_file, "%c", output);
        }
        fprintf(level_file, "\n");
    }

    // saving background

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            char output;

            Object* obj = &background[y][x];

            if (obj->type != EMPTY)
            {
                if (obj->bitmap == bitmap_bush)
                    output = 'b';
                else if (obj->bitmap == bitmap_bush_big)
                    output = 'B';
                else if (obj->bitmap == bitmap_hill_top)
                    output = '^';
                else if (obj->bitmap == bitmap_hill_middle_patterned_left)
                    output = '<';
                else if (obj->bitmap == bitmap_hill_middle_patterned_right)
                    output = '>';
                else if (obj->bitmap == bitmap_hill_middle)
                    output = '_';
                else if (obj->bitmap == bitmap_hill_slope_right)
                    output = '\\';
                else if (obj->bitmap == bitmap_hill_slope_left)
                    output = '/';
                else if (obj->bitmap == bitmap_tree_bottom)
                    output = '|';
                else if (obj->bitmap == bitmap_tree_small)
                    output = 'o';
                else if (obj->bitmap == bitmap_tree)
                    output = 'O';
            }
            else
                output = '0';

            fprintf(level_file, "%c", output);
            }
        fprintf(level_file, "\n");
    }
    // saving objects

    for (int i = 0; i < non_static_elements->size; i++)
    {
        Object* obj = get_element_pointer_ol(non_static_elements, i);

        int pos_x;
        int pos_y;
        char type;

        if (obj->type <= 3 || obj->type == COIN)
        {
            type = obj->type == COIN ? '$' : obj->type + '0';
            pos_x = obj->pos_x;
            pos_y = obj->pos_y;

            fprintf(level_file, "%c-%d;%d.\n", type, pos_x, pos_y);
        }
    }

    fclose(level_file);
}

void load_level(char* path, Object level[MAP_HEIGHT][MAP_WIDTH], Object background_elements[MAP_HEIGHT][MAP_WIDTH], ObjectsList* non_static_objects, ObjectsList* clouds)
{
    FILE* level_file;
    level_file = fopen(path, "r");

    non_static_objects->size = 0;
    non_static_objects->first = 0;
    clouds->size = 0;
    clouds->first = 0;

    if (!level_file)
    {
        printf("Failed to open %s!\n", path);
        exit(-1);
    }

    char line[MAP_WIDTH + 2];

    for (int e = 0; e < 2; e++)
    {
        for (int i = 0; i < MAP_HEIGHT; i++)
        {
            if (!fgets(line, MAP_WIDTH + 2, level_file))
            {
                printf("Error during loading %s!\n", path);
                exit(-1);
            }

            if (e == 0)
                parse_map_line(level, i, line);
            else
                parse_background_line(background_elements, i, line);
        }
    }

    while (fgets(line, MAP_WIDTH + 2, level_file))
    {
        parse_object_line(non_static_objects, line);
    }

    generate_clouds(clouds);

    // // creating finish flag at the end of the level
    Object finish_flag;
    bind_bitmap(&finish_flag, bitmap_finish_flag);
    Physics flag_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    init_object(&finish_flag, FINISH_LINE, (MAP_WIDTH - 9) * 64, (MAP_HEIGHT - 5) * 64, 64, 128, RECTANGLE, (MAP_WIDTH - 10) * 64, 0, 128, MAP_HEIGHT * 64, flag_physics, 1);
    level[MAP_HEIGHT - 4][MAP_WIDTH - 6] = finish_flag;

    fclose(level_file);
}

void parse_map_line(Object level[MAP_HEIGHT][MAP_WIDTH], int line_number, char* line_str)
{
    Object obj;
    Physics static_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    for (int x = 0; x < MAP_WIDTH; x++)
    {
        if (line_str[x] == '\0')
        {
            printf("Error while parsing map information! (%d%s line too short)\nx = %d, line: %s\n", line_number, line_number % 10 == 1 ? "st" : line_number % 10 == 2 ? "nd" : line_number % 10 == 3 ? "rd" : "th", x, line_str);
            exit(-1);
        }
        else
        {
            int type = -1;
            float coin_number = 0.0f;
            int frames_number = 1;
            int size_x = 64;
            int size_y = 64;

            switch (line_str[x])
            {
                case '#':
                    bind_bitmap(&obj, bitmap_brick);
                    type = NORMAL_BLOCK;
                    break;
                case '@':
                    bind_bitmap(&obj, bitmap_brick_floor);
                    type = NORMAL_BLOCK;
                    break;
                case '$':
                    bind_bitmap(&obj, bitmap_secret_brick);
                    type = SECRET_BLOCK;
                    coin_number = 1.0f;
                    frames_number = 2;
                    break;
                case '&':
                    bind_bitmap(&obj, bitmap_secret_brick);
                    type = SECRET_BLOCK_MUSHROOM;
                    frames_number = 2;
                    break;
                case '5':
                    bind_bitmap(&obj, bitmap_secret_brick);
                    type = SECRET_BLOCK;
                    coin_number = 5.0f;
                    frames_number = 2;
                    break;
                case '>':
                    bind_bitmap(&obj, bitmap_cannon);
                    type = CANNON_RIGHT;
                    size_y = 128;
                    break;
                case '<':
                    bind_bitmap(&obj, bitmap_cannon);
                    type = CANNON_LEFT;
                    size_y = 128;
                    break;
                case '!':
                    bind_bitmap(&obj, bitmap_brick_unbreakable);
                    type = UNBREAKABLE_BLOCK;
                    break;
                case 'L':
                    bind_bitmap(&obj, bitmap_pipe_top_left);
                    type = UNBREAKABLE_BLOCK;
                    break;
                case 'l':
                    bind_bitmap(&obj, bitmap_pipe_left);
                    type = UNBREAKABLE_BLOCK;
                    break;
                case 'R':
                    bind_bitmap(&obj, bitmap_pipe_top_right);
                    type = UNBREAKABLE_BLOCK;
                    break;
                case 'r':
                    bind_bitmap(&obj, bitmap_pipe_right);
                    type = UNBREAKABLE_BLOCK;
                    break;
                case '0':
                    frames_number = 0;
                    type = EMPTY;
                    break;
                default:
                    printf("Unexpected object type (%c) in the level file!\n", line_str[x]);
                    exit(-1);
            }

            init_object(&obj, type, x*64, line_number*64, size_x, size_y, RECTANGLE, x*64, line_number*64, size_x, size_y, static_physics, frames_number);
            obj.physics.mass = coin_number;

            level[line_number][x] = obj;
        }
    }
}

void parse_background_line(Object background_elements[MAP_HEIGHT][MAP_WIDTH], int line_number, char* line_str)
{
    Object obj;
    Physics static_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    for (int x = 0; x < MAP_WIDTH; x++)
    {
        if (line_str[x] == '\0')
        {
            printf("Error while parsing background information! (%d%s line too short)\nx = %d, line: %s\n", line_number, line_number % 10 == 1 ? "st" : line_number % 10 == 2 ? "nd" : line_number % 10 == 3 ? "rd" : "th", x, line_str);
            exit(-1);
        }
        else
        {
            int size_x = 64;
            int size_y = 64;
            int type = BACKGROUND;

            switch (line_str[x])
            {
                case 'b':
                    bind_bitmap(&obj, bitmap_bush);
                    size_x = 128;
                    size_y = 64;
                    break;
                case 'B':
                    bind_bitmap(&obj, bitmap_bush_big);
                    size_x = 192;
                    size_y = 68;
                    break;
                case '#':
                    bind_bitmap(&obj, bitmap_fence);
                    break;
                case '^':
                    bind_bitmap(&obj, bitmap_hill_top);
                    break;
                case '>':
                    bind_bitmap(&obj, bitmap_hill_middle_patterned_right);
                    break;
                case '<':
                    bind_bitmap(&obj, bitmap_hill_middle_patterned_left);
                    break;
                case '_':
                    bind_bitmap(&obj, bitmap_hill_middle);
                    break;
                case '\\':
                    bind_bitmap(&obj, bitmap_hill_slope_right);
                    break;
                case '/':
                    bind_bitmap(&obj, bitmap_hill_slope_left);
                    break;
                case '|':
                    bind_bitmap(&obj, bitmap_tree_bottom);
                    break;
                case 'o':
                    bind_bitmap(&obj, bitmap_tree_small);
                    break;
                case 'O':
                    bind_bitmap(&obj, bitmap_tree);
                    size_y = 128;
                    break;
                case '0':
                    type = EMPTY;
                    break;
                default:
                    printf("Unexpected object type (%c) in the level file!\n", line_str[x]);
                    exit(-1);
            }

            init_object(&obj, type, x*64, line_number*64, size_x, size_y, RECTANGLE, x*64, line_number*64, size_x, size_y, static_physics, 1);
            background_elements[line_number][x] = obj;
        }
    }
}

void parse_object_line(ObjectsList* list, char* line)
{
    Physics goomba_physics = create_physics(3.0f, 0.0f, 3.0f, 20.0f, 1.0f);
    Physics koopa_physics  = create_physics(-3.0f, 0.0f, 3.0f, 20.0f, 2.0f);
    Physics flying_koopa_physics = create_physics(-3.0f, 0.0f, 3.0f, 13.0f, 0.5f);
    Physics static_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    char type = line[0];
    int pos_x;
    int pos_y;

    int i = 2;

    char str[8];
    memset(str, '\0', sizeof(str));

    while(line[i] != ';')
    {
        str[i - 2] = line[i];
        i++;
    }

    pos_x = atoi(str);
    int len = (int)strlen(str);

    memset(str, '\0', sizeof(str));
    i++;
    while(line[i] != '.')
    {
        str[i - 2 - len - 1] = line[i];
        i++;
    }

    pos_y = atoi(str);

    Object obj;

    switch (type)
    {
        case '0': // goomba
            bind_bitmap(&obj, bitmap_enemy_goomba);
            init_object(&obj, ENEMY_GOOMBA, pos_x, pos_y, 64, 64, RECTANGLE, pos_x + 7, pos_y + 8, 50, 56, goomba_physics, 2);
            push_back_ol(list, obj);
            return;
        case '1': // koopa
            bind_bitmap(&obj, bitmap_enemy_koopa);
            init_object(&obj, ENEMY_KOOPA, pos_x, pos_y, 96, 80, RECTANGLE, pos_x + 16, pos_y - 16, 64, 80, koopa_physics, 4);
            push_back_ol(list, obj);
            return;
        case '2': // koopa flying
            bind_bitmap(&obj, bitmap_enemy_koopa);
            init_object(&obj, ENEMY_KOOPA_FLYING, pos_x, pos_y, 96, 80, RECTANGLE, pos_x + 16, pos_y - 16, 64, 80, flying_koopa_physics, 4);
            obj.animation_frame = 5;
            push_back_ol(list, obj);
            return;
        case '3': // piranha plant
            bind_bitmap(&obj, bitmap_plant);
            init_object(&obj, ENEMY_PIRANHA_PLANT, pos_x, pos_y, 128, 128, RECTANGLE, pos_x + 32, pos_y + 48, 64, 80, static_physics, 4);
            obj.animation_frame = 2;
            push_back_ol(list, obj);
            return;
        case '$': // coin
            bind_bitmap(&obj, bitmap_secret_brick);
            init_object(&obj, COIN, pos_x, pos_y, 64, 64, RECTANGLE, pos_x + 21, pos_y, 24, 64, static_physics, 1);
            obj.animation_frame = 3;
            obj.alive = false;
            push_back_ol(list, obj);
            return;
        default:
            printf("Unexpected non-static object type (%c)!\n", type);
            exit(-1);
    }
}

void generate_clouds(ObjectsList* clouds)
{
    const int top_y = 128;
    const int bottom_y = 7*64;

    Physics cloud_physics = create_physics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Object cloud;

    int seed;
    time_t t;
    seed = time(&t);
    srand(seed);

    for (int x = 128; x < (MAP_WIDTH-1) * 64; x += 512)
    {
        int width = 128;

        if (rand() % 3)
            bind_bitmap(&cloud, bitmap_cloud);
        else
        {
            bind_bitmap(&cloud, bitmap_cloud_big);
            width = 192;
        }

        int y = rand() % (bottom_y - top_y);
        int x_rand = rand() % 64;

        init_object(&cloud, BACKGROUND, x - x_rand, y, width, 128, RECTANGLE, 0, 0, 1, 1, cloud_physics, 1);
        push_back_ol(clouds, cloud);
    }
}
