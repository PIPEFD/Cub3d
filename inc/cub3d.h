#ifndef CUB_3D_H

#define CUB_3D_H



#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include "../mlx/include/MLX42/MLX42.h"

#include "../mlx/include/MLX42/MLX42.h"
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <float.h>

#define WINDOW_WIDTH   (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT  (MAP_NUM_ROWS * TILE_SIZE)
#define TILE_SIZE 64
#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15
#define MINIMAP_SCALE_FACTOR 1.0
#define NUM_RAYS WINDOW_WIDTH
#define PI 3.14159265
#define TWO_PI (2 * PI)
#define FOV (60 * (PI / 180))
#define FRAME_TIME_LENGTH (1000 / 60) // 60 frames per second


// mlx_t* mlx;
// mlx_image_t* img;

// t_player player;
// t_ray ray[NUM_RAYS];

uint32_t ticksLastFrame = 0;



const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

typedef struct s_player
{
    float x;
    float y;
    float width;
    float height;
    int turnDirection; // -1 for left, +1 for right
    int walkDirection; // -1 for back, +1 for front
    float rotationAngle;
    float walkSpeed;
    float turnSpeed;
} t_player;

typedef struct s_ray
{
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float distance;
    int wasHitVertical;
    int isRayFacingUp;
    int isRayFacingDown;
    int isRayFacingLeft;
    int isRayFacingRight;
    int wallHitContent;
} t_ray[NUM_RAYS];

void draw_rectangle(mlx_image_t* img, int x, int y, int width, int height, uint32_t color);
void draw_line(mlx_image_t* img, int x0, int y0, int x1, int y1, uint32_t color);
void key_hook(mlx_key_data_t keydata, t_player *player, mlx_t *mlx);
int mapHasWallAt(float x, float y);
void renderPlayer();
void movePlayer(float deltaTime, t_player *player, mlx_t *mlx, mlx_image_t *img, t_ray *ray);
void castRay(float rayAngle, int stripid, t_player *player, mlx_t *mlx, mlx_image_t *img, t_ray *ray);
void castAllRays();
void renderRays();
void renderMap();
void update(t_player *player, mlx_t *mlx, mlx_image_t *img, t_ray *ray);
void setup(mlx_t *mlx);
float normalizeAngle(float angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);

#endif