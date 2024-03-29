#ifndef _GLOBAL_
#define _GLOBAL_

#define FALSE 0
#define TRUE 1

#define PI 3.14159265
#define TWO_PI 6.28318530

#define TILE_SIZE 64
#define MAP_NUM_ROWS 15
#define MAP_NUM_COLS 15
#define NUM_TEXTURES 6

#define MINIMAP_SCALE_FACTOR 0.20

#define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64

#define FOV_ANGLE (60 * (PI / 180))

#define NUM_RAYS WINDOW_WIDTH

#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)

#endif /* _GLOBAL_ */