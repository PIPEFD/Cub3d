#ifndef CUB_3D_H

#define CUB_3D_H



#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include "../mlx/include/MLX42/MLX42.h"

#define FALSE 0
#define TRUE 1

// #define WINDOW_WIDTTH 800
// #define WINDOW_HEIGHT 600
#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)
#define PI 3.14159265359
#define TWO_PI 6.28318530

#define TILE_SIZE 64
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define MINIMAP_SCALE_FACTOR 1.0

#define WINDOW_WIDTH   (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT  (MAP_NUM_ROWS * TILE_SIZE)

#define FOV (60 *( PI / 180))
#define WALL_STRIP_WIDTH  1
#define NUM_RAYS	WINDOW_WIDTH

# define BLACK_2    0x000000
# define WHITE_2	0xFFFFFF
# define RED_2      0xFF0000
# define GREEN_2  	0x00FF00
# define BLUE_2   	0x0000FF
# define YELLOW_2 	0xFFFF00
# define MAGENTA_2	0xFF00FF
# define CYAN_2   	0x00FFFF
# define PSYCHEDELIC_0  0xFF1493  // Rosa fuerte
# define PSYCHEDELIC_1  0x9400D3  // Violeta
# define PSYCHEDELIC_2  0x00CED1  // Turquesa
# define PSYCHEDELIC_3  0xFFD700  // Dorado
# define PSYCHEDELIC_4  0x32CD32  // Verde lima
# define PSYCHEDELIC_5  0x8A2BE2  // Azul lavanda
# define MSG_N "INVALID ARGUMENTS!\n"


typedef struct s_map        t_map;
typedef struct s_player     t_player;
typedef struct s_philo      t_philo;
typedef struct s_game       t_game;
typedef struct s_ray        t_ray[NUM_RAYS];




struct s_t_game
{
    void    *mlx_win;
    void    *mlx;
    void    *addr;
    char    *ptr;


    t_player player;
};


struct s_t_map
{
    /* data */
};


struct s_player
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
	// int fov;

};

struct s_ray
{
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	int		wasHitVertical;
	int isRayFacingUp;
	int isRayFacingDown;
	int isRayFacingLeft;
	int isRayFacingRight;
	int wallHitContent;
};


#endif