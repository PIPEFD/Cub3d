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
// --- // --- // --- // --- // --- //
# define MINIMAP_SCALE_FACTOR 0.3
# define PI 3.14159265
# define TWO_PI (2 * PI)
# define FOV (60 * (PI / 180))
# define FRAME_TIME_LENGTH (1000 / 60) // 60 frames per second

typedef struct s_ray_cast
{
	// Direcciones del rayo
	int				isRayFacingDown;
	int				isRayFacingUp;
	int				isRayFacingRight;
	int				isRayFacingLeft;

	// Interceptos y pasos
	float			xintercept;
	float			yintercept;
	float			xstep;
	float			ystep;

	// Información de impacto horizontal
	int				foundHorzWallhit;
	float			horWallHitX;
	float			horWallHitY;
	int				horWallContent;

	// Información de impacto vertical
	int				foundVerWallhit;
	float			verWallHitX;
	float			verWallHitY;
	int				verWallContent;

	// Próximos puntos de intersección
	float			nextHorzTouchX;
	float			nextHorzTouchY;
	float			nextVerTouchX;
	float			nextVerTouchY;

	// Distancias
	float			horHitDistance;
	float			verHitDistance;
}					t_ray_cast;
typedef struct s_player
{
	float			x;
	float			y;
	float			width;
	float			height;
	int turnDirection;   // -1 for left, +1 for right
	int walkDirection;   // -1 for back, +1 for front
	int strafeDirection; // -1 para izquierda, +1 para derecha
	float			rotationAngle;
	float			walkSpeed;
	float			turnSpeed;
}					t_player;

typedef struct s_ray
{
	float			rayAngle;
	float			wallHitX;
	float			wallHitY;
	float			distance;
	int				wasHitVertical;
	int				isRayFacingUp;
	int				isRayFacingDown;
	int				isRayFacingLeft;
	int				isRayFacingRight;
	int				wallHitContent;
}					t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	t_ray			rays[NUM_RAYS];
	t_ray_cast		ray_casts[NUM_RAYS];
	unsigned int	ticksLastFrame;
	char			**map;

}					t_game;

// Funciones de parseo y estrucuturacion del mapa //
// --- // --- // --- // --- // --- //
// Funciones para la inicializacion de la estructura
// --- // --- // --- // --- // --- //

int					init_data_map(t_game *game);
int					init_data_player(t_game *game, const char *directionInput);
int					data_init_rays(t_game *game);
// --- // --- // --- // --- // --- //
int					set_player_direction(t_player *player,
						const char *directionInput);
// Añadido

// --- // --- // --- // --- // --- // // --- // --- // --- // --- // --- //
// FUNCIONES PARA GENERA EL RAYCASTING EN MLX Y RENDERIZAR EL MAPA
// LOS RAYOS CON BASE EN LA POSICIÓN DEL JUGADOR...
// --- // --- // --- // --- // --- // // --- // --- // --- // --- // --- //
// Function for draw a rectangle form in mlx

void				draw_rectangle(mlx_image_t *img, int x, int y, int width,
						int height, uint32_t color);

// Fuunction for draw a line in mlx
void				draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1,
						uint32_t color);

void				destroy_window(t_game *game);

// Function for update postion of player position
void				key_hook(mlx_key_data_t keydata, void *param);

// -- // -- // --- // -- //
int	map_has_wall_at(t_game *game, float x, float y);
int					move_player(t_game *game, float deltaTime);
// --- // --- // --- // --- // --- //
// Funciones para determinar la poscionde del rayo en un plano 2D
// Ademas de Funciones auxiliares para realizar el calculo
// de la vista a la cual se dirijean los rayos ademas
// de las intercepciones para determinar el chocque de los rayos
// con los muros en el angulo de vision establecido
// --- // --- // --- // --- // --- //

void				cast_ray(t_game *game, float rayAngle, int stripid);
void				cast_all_rays(t_game *game);
int					determineRayDirection(t_ray_cast *ray_cast, float rayAngle);
void				calculateDistances(t_ray_cast *ray_cast, t_player *player);
void				determineClosestHit(t_ray_cast *ray_cast, t_ray *ray);
void				updateRayProperties(t_ray *ray, t_ray_cast *ray_cast,
						float rayAngle);
void				castVerticalRay(t_game *game, t_ray_cast *ray_cast,
						float rayAngle);
void				castHorizontalRay(t_game *game, t_ray_cast *ray_cast,
						float rayAngle);
void				findHorizontalIntersection(t_game *game,
						t_ray_cast *ray_cast);

// --- // --- // --- // --- // --- //

void				render_rays(t_game *game);
void				render_player(t_game *game);
int					render_map(t_game *game);
void				update(void *param);
int					setup(t_game *game, const char *direction_input);
float				normalize_angle(float angle);
float				distance_between_points(float x1, float y1, float x2,
						float y2);

void				render_3d_projection(t_game *game);

// Funciones para agres sprites y texturas al juego //

#endif
