#include "level.h"

void load_level(char* path, Object level[MAP_HEIGHT][MAP_WIDTH], Object background_elements[MAP_HEIGHT][MAP_WIDTH], ObjectsList* non_static_objects, ObjectsList*)
{
    FILE* level_file;
    level_file = fopen(path, "r");;

    if (!level_file)
    {
        printf("Failed to open %s!\n", path);
        exit(-1);
    }

    char line[256];

    for (int e = 0; e < 2; e++)
    {
        for (int i = 0; i < MAP_HEIGHT; i++)
        {
            if (!fgets(line, 256, level_file))
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

    while (fgets(line, 256, level_file))
    {
        parse_object_line(non_static_objects, line);
    }

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
            printf("Error while parsing map information! (%d%s line too short)\n", line_number, line_number % 10 == 1 ? "st" : line_number % 10 == 2 ? "nd" : line_number % 10 == 3 ? "rd" : "th");
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
                    frames_number 2;
                    break;
                case '&':
                    bind_bitmap(&obj, bitmap_secret_brick);
                    type = SECRET_BLOCK_MUSHROOM;
                    frames_number 2;
                    break;
                case '5':
                    bind_bitmap(&obj, bitmap_secret_brick);
                    type = SECRET_BLOCK;
                    coin_number = 5.0f;
                    frames_number 2;
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
            obj.mass = coin_number;

            level[line_number][x] = obj;
        }
    }
}

void parse_background_line(Object background_elements[MAP_HEIGHT][MAP_WIDTH], int line_number, char* line_str)
{

}

void parse_object_line(ObjectsList* list, char* line)
{
    Physics goomba_physics = create_physics(3.0f, 0.0f, 3.0f, 20.0f, 1.0f);
    Physics koopa_physics  = create_physics(-3.0f, 0.0f, 3.0f, 20.0f, 2.0f);
    Physics flying_koopa_physics = create_physics(-3.0f, 0.0f, 3.0f, 13.0f, 0.5f);
}
