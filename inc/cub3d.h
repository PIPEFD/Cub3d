#ifndef CUB_3D_H
# define CUB_3D_H

//

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/inc/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// --- // --- // --- // --- // --- //
// Librerias no permitidas por el proyecto
// --- // --- // --- // --- // --- //
# include <float.h>
# include <stdint.h>
# include <string.h>
// --- // --- // --- // --- // --- //

// --- // --- // --- // --- // --- //
// Harcodeo de informacion del mapa //
# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
# define TILE_SIZE 64
# define MAP_NUM_ROWS 11
# define MAP_NUM_COLS 15
# define NUM_RAYS WINDOW_WIDTH
#define PLAYER_SIZE 5 // Tamaño del jugador en píxeles en el minimapa

// --- // --- // --- // --- // --- //
# define MINIMAP_SCALE_FACTOR 0.3
# define PI 3.14159265
# define TWO_PI (2 * PI)
# define FOV (60 * (PI / 180))
# define FRAME_TIME_LENGTH (1000 / 60) // 60 frames per second


typedef struct s_render_params
{
	float				perp_distance;
	float				distance_proj_plane;
	float				wall_strip_height;
	int					wall_top_pixel;
	int					wall_bottom_pixel;
	unsigned int		wall_color;
}						t_render_params;

typedef struct s_rectangle_params
{
	int					x;
	int					y;
	int					width;
	int					height;
	unsigned int		color;
}						t_rectangle_params;

typedef struct s_line_params
{
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	unsigned int		color;
}						t_line_params;

typedef struct s_bresenham_vars {
    int x0;
    int y0;
    int x1;
    int y1;
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;
} t_bresenham_vars;
typedef struct s_line_draw_params {
    mlx_image_t *img;
    int x0;
    int y0;
    int x1;
    int y1;
    unsigned int color;
} t_line_draw_params;

typedef struct s_draw_figures
{
	t_rectangle_params	*rect_params;
	t_line_params		*line_params;
	t_line_draw_params	*line_draw;
	// Puedes agregar más tipos de figuras en el futuro
}						t_draw_figures;

typedef struct s_ray_cast
{
	// Direcciones del rayo
	int					isRayFacingDown;
	int					isRayFacingUp;
	int					isRayFacingRight;
	int					isRayFacingLeft;

	// Interceptos y pasos
	float				xintercept;
	float				yintercept;
	float				xstep;
	float				ystep;

	// Información de impacto horizontal
	int					foundHorzWallhit;
	float				horWallHitX;
	float				horWallHitY;
	int					horWallContent;

	// Información de impacto vertical
	int					foundVerWallhit;
	float				verWallHitX;
	float				verWallHitY;
	int					verWallContent;

	// Próximos puntos de intersección
	float				nextHorzTouchX;
	float				nextHorzTouchY;
	float				nextVerTouchX;
	float				nextVerTouchY;

	// Distancias
	float				horHitDistance;
	float				verHitDistance;
}						t_ray_cast;
typedef struct s_player
{
	float				x;
	float				y;
	float				width;
	float				height;
	int turnDirection;   // -1 for left, +1 for right
	int walkDirection;   // -1 for back, +1 for front
	int strafeDirection; // -1 para izquierda, +1 para derecha
	float				rotationAngle;
	float				walkSpeed;
	float				turnSpeed;
}						t_player;

typedef struct s_ray
{
	float				rayAngle;
	float				wallHitX;
	float				wallHitY;
	float				distance;
	int					wasHitVertical;
	int					isRayFacingUp;
	int					isRayFacingDown;
	int					isRayFacingLeft;
	int					isRayFacingRight;
	int					wallHitContent;
}						t_ray;

typedef struct s_game
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	t_player			player;
	t_render_params		render_params;
	t_draw_figures		draw_figures;
	t_ray_cast			ray_casts[NUM_RAYS];
	t_ray				rays[NUM_RAYS];
	unsigned int		ticksLastFrame;
	char				**map;

}						t_game;

// Funciones de parseo y estrucuturacion del mapa //
// --- // --- // --- // --- // --- //
// Funciones para la inicializacion de la estructura
// --- // --- // --- // --- // --- //
int						init_data_bresenham(t_bresenham_vars *vars, 
							t_line_params *params);
int						init_data_all(t_game *game,
							const char *direction_input);
int						init_data_map(t_game *game);
int						init_data_player(t_game *game,
							const char *directionInput);
int						init_data_rays(t_game *game);
int						init_data_figures(t_game *game);
int						init_data_render(t_game *game, int i);

// --- // --- // --- // --- // --- //

// Funciones para setear la dirección del jugador

// --- // --- // --- // --- // --- //
int						set_player_direction(t_player *player,
							const char *directionInput);
// Añadido

// --- // --- // --- // --- // --- //
// Function for update postion of player position
int						move_player(t_game *game, float deltaTime);
// --- // --- // --- // --- // --- //

// --- // --- // --- // --- // --- //
 /*FUNCIONES PARA GENERA EL RAYCASTING EN MLX Y RENDERIZAR EL MAPA
 LOS RAYOS CON BASE EN LA POSICIÓN DEL JUGADOR...*/
// --- // --- // --- // --- // --- // // --- // --- // --- // --- // --- //
// Function for draw a rectangle form in mlx

// --- // --- // --- // --- // --- //

	/* 
	Funcion para dibujar una linea recta en mlx con base 
	en el algoritmo de bresenham
	*/
// --- // --- // --- // --- // --- //
int draw_line(t_game *game);

// --- // --- // --- // --- // --- //
	/*
	Funcion para dibujar un rectangulo en mlx
	*/

// --- // --- // --- // --- // --- //
int draw_rectangle(t_game *game);


// void					draw_rectangle(mlx_image_t *img, int x, int y,
// 							int width, int height, uint32_t color);

// // Fuunction for draw a line in mlx
// void					draw_line(mlx_image_t *img, int x0, int y0, int x1,
// 							int y1, uint32_t color);

void					destroy_window(t_game *game);

void					key_hook(mlx_key_data_t keydata, void *param);

// -- // -- // --- // -- //
int						map_has_wall_at(t_game *game, float x, float y);
// --- // --- // --- // --- // --- //
// Funciones para determinar la poscionde del rayo en un plano 2D
// Ademas de Funciones auxiliares para realizar el calculo
// de la vista a la cual se dirijean los rayos ademas
// de las intercepciones para determinar el chocque de los rayos
// con los muros en el angulo de vision establecido
// --- // --- // --- // --- // --- //

// void					cast_ray(t_game *game, float rayAngle, int stripid);

int	initialize_ray(t_game *game, float *rayAngle, int stripid);
int	calculate_hit_distances(t_game *game, t_ray_cast *ray_cast, int stripid);
int	assign_ray_properties(t_game *game, float rayAngle, int stripid);

void					cast_all_rays(t_game *game);
int	cast_ray_setup(t_game *game, float rayAngle, int stripid);
int	find_horizontal_hit(t_game *game, t_ray_cast *ray_cast, t_player *player, float rayAngle);
int	find_vertical_hit(t_game *game, t_ray_cast *ray_cast,
		t_player *player, float rayAngle);




// --- // --- // --- // --- // --- //

void					render_rays(t_game *game);
void					render_player(t_game *game);
int						render_map(t_game *game);
void					update(void *param);
int						setup(t_game *game, const char *direction_input);
float					normalize_angle(float angle);
float					distance_between_points(float x1, float y1, float x2,
							float y2);

void					render_3d_projection(t_game *game);

// Funciones para agres sprites y texturas al juego //

#endif
