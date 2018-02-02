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

    for (int x = 0; x < MAP_WIDTH; x++)
    {
        if (line_str[x] == '\0')
        {
            printf("Error while parsing map information!\n");
            exit(-1);
        }
        else
        {
            switch (line_str[x])
            {
                case '#'
            }
        }
    }
}

void parse_background_line(Object background_elements[MAP_HEIGHT][MAP_WIDTH], int line_number, char* line_str)
{

}

void parse_object_line(ObjectsList* list, char* line)
{

}
