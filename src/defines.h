#ifndef _DEFINES
#define _DEFINES

// Display properties
#define DISPLAY_HEIGHT 720
#define DISPLAY_WIDTH 1280
#define FPS 60

// Map properties
#define MAP_WIDTH   256
#define MAP_HEIGHT  16
#define RENDER_DISTANCE 64*32

// Colors
#define BLACK       al_map_rgba(0  , 0  , 0  , 255)
#define WHITE       al_map_rgba(255, 255, 255, 255)
#define RED         al_map_rgba(255, 0  , 0  , 255)
#define GREEN       al_map_rgba(0  , 255, 0  , 255)
#define BLUE        al_map_rgba(0  , 0  , 255, 255)
#define YELLOW      al_map_rgba(255, 255, 0  , 255)
#define CYAN        al_map_rgba(0  , 255, 255, 255)
#define PURPLE      al_map_rgba(255, 0  , 255, 255)
#define LIGHT_GRAY  al_map_rgba(200, 200, 200, 255)
#define LIGHT_BLUE  al_map_rgba(92 , 150, 252, 255) // actual NES Mario sky color
#define GRAY        al_map_rgba(120, 120, 120, 255)
#define DARK_GRAY   al_map_rgba(50 , 50 , 50 , 255)
#define DARK_RED    al_map_rgba(155, 0  , 0  , 255)
#define DARK_GREEN  al_map_rgba(0  , 155, 0  , 255)
#define DARK_BLUE   al_map_rgba(0  , 0  , 155, 255)
#define OPAQUE_RED  al_map_rgba(255, 0  , 0  , 127)

#endif
