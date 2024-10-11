#ifndef CUB_3D_H


#define CUB_3D_H

// 
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

// --- // --- // --- // --- // --- //
// Harcodeo de informacion del mapa //
#define WINDOW_WIDTH   (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT  (MAP_NUM_ROWS * TILE_SIZE)
#define TILE_SIZE 64
#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15
#define NUM_RAYS WINDOW_WIDTH
// --- // --- // --- // --- // --- //
#define MINIMAP_SCALE_FACTOR 0.3
#define PI 3.14159265
#define TWO_PI (2 * PI)
#define FOV (60 * (PI / 180))
#define FRAME_TIME_LENGTH (1000 / 60) // 60 frames per second


// const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
//     {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
//     {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// };



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
} t_ray;


typedef struct s_game
{
    mlx_t* mlx;
    mlx_image_t* img;
    t_player player;
    t_ray rays[NUM_RAYS];
    uint32_t ticksLastFrame;
    char** map;

} t_game;

// Funciones de parseo y estrucuturacion del mapa //


// --- // --- // --- // --- // --- // // --- // --- // --- // --- // --- //
    // FUNCIONES PARA GENERA EL RAYCASTING EN MLX Y RENDERIZAR EL MAPA
    // LOS RAYOS CON BASE EN LA POSICIÓN DEL JUGADOR...
// --- // --- // --- // --- // --- // // --- // --- // --- // --- // --- //
// Function for draw a rectangle form in mlx


void draw_rectangle(mlx_image_t* img, int x, int y, int width, int height, uint32_t color);

//Fuunction for draw a line in mlx
void draw_line(mlx_image_t* img, int x0, int y0, int x1, int y1, uint32_t color);

void destroyWindow(t_game* game);

//Function for update postion of player position
void key_hook(mlx_key_data_t keydata, void* param);

// -- // -- // --- // -- //
int mapHasWallAt(t_game* game, float x, float y);
void renderPlayer(t_game* game);
void movePlayer(t_game* game, float deltaTime);
void castAllRays(t_game* game);
void castAllRays(t_game* game);
void renderRays(t_game* game);
void renderMap(t_game* game);
void update(void* param);
void setup(t_game* game);
float normalizeAngle(float angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);


void render3DProjection(t_game* game);


// Funciones para agres sprites y texturas al juego //




#endif