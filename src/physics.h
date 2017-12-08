#include <stdbool.h>

#ifndef _PHYSICS
#define _PHYSICS

typedef struct
{
    int velocity_x;
    int velocity_y;
    int acceleration;
    bool gravity;
    int mass;

} Physics;

Physics generate_static_physics();
Physics create_physics(int velocity_x, int velocity_y, int acceleration, bool gravity, int mass);
#endif
