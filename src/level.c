#include "level.h"

void load_level(char* path, Object level[MAP_HEIGHT][MAP_WIDTH], Object background_elements[MAP_HEIGHT][MAP_WIDTH], ObjectsList* non_static_objects, ObjectsList* clouds)
{
    FILE* level_file;
    level_file = fopen(path, "r");;

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
                    break;
                case '<':
                    bind_bitmap(&obj, bitmap_cannon);
                    type = CANNON_LEFT;
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

            init_object(&obj, type, x*64, line_number*64, 64, 64, RECTANGLE, x*64, line_number*64, 64, 64, static_physics, frames_number);
            obj.physics.mass = coin_number;

            level[line_number][x] = obj;
        }
    }
}

void parse_background_line(Object background_elements[MAP_HEIGHT][MAP_WIDTH], int line_number, char* line_str)
{
    // TODO
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
    i++;

    pos_x = atoi(str);
    memset(str, '\0', sizeof(str));

    while(line[i] != '.')
    {
        str[i - 2] = line[i];
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

}
