/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:33:21 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/21 11:37:55 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "structs.h"
# include "utils.h"


int 	parsing(t_game *game, char *file_name);
// Funciones de parseo y estrucuturacion del mapa //
// --- // --- // --- // --- // --- //
// Funciones para la inicializacion de la estructura
// --- // --- // --- // --- // --- //
int		init_data_bresenham(t_bresenham_vars *vars, t_line_params *params);
int		init_data_all(t_game *game, const char *direction_input);
int		init_data_map(t_game *game);
int		init_data_player(t_game *game, const char *directionInput);
int		init_data_rays(t_game *game);
int		init_data_figures(t_game *game);
int		init_data_render(t_game *game, int i);

// --- // --- // --- // --- // --- //

// Funciones para setear la dirección del jugador

// --- // --- // --- // --- // --- //
int		set_player_direction(t_player *player, const char *directionInput);
// Añadido

// --- // --- // --- // --- // --- //
// Function for update postion of player position
void	move_player(t_game *game, float deltaTime);
// --- // --- // --- // --- // --- //

// --- // --- // --- // --- // --- //
 /*FUNCIONES PARA GENERA EL RAYCASTING EN MLX Y RENDERIZAR EL MAPA
 LOS RAYOS CON BASE EN LA POSICIÓN DEL JUGADOR...*/
// --- // --- // --- // --- // --- // // --- // --- // --- // --- // --- //
// Function for draw a rectangle form in mlx

/* --- // --- // --- // --- // --- //
	Funcion para dibujar una linea recta en mlx con base en el algoritmo de bresenham
// --- // --- // --- // --- // --- */
int		draw_line(t_game *game);

/* --- // --- // --- // --- // --- //
	Funcion para dibujar un rectangulo en mlx
// --- // --- // --- // --- // --- */
int		draw_rectangle(t_game *game);


// void					draw_rectangle(mlx_image_t *img, int x, int y,
// 							int width, int height, uint32_t color);

// // Fuunction for draw a line in mlx
// void					draw_line(mlx_image_t *img, int x0, int y0, int x1,
// 							int y1, uint32_t color);

void	destroy_window(t_game *game);

void	key_hook(mlx_key_data_t keydata, void *param);

// -- // -- // --- // -- //
int		map_has_wall_at(t_game *game, float x, float y);
// --- // --- // --- // --- // --- //
// Funciones para determinar la poscionde del rayo en un plano 2D
// Ademas de Funciones auxiliares para realizar el calculo
// de la vista a la cual se dirijean los rayos ademas
// de las intercepciones para determinar el chocque de los rayos
// con los muros en el angulo de vision establecido
// --- // --- // --- // --- // --- //

// void					cast_ray(t_game *game, float rayAngle, int stripid);

int		initialize_ray(t_game *game, float *rayAngle, int stripid);
int		calculate_hit_distances(t_game *game, t_ray_cast *ray_cast, int stripid);
int		assign_ray_properties(t_game *game, float rayAngle, int stripid);

void	cast_all_rays(t_game *game);
int		cast_ray_setup(t_game *game, float rayAngle, int stripid);
int		find_horizontal_hit(t_game *game, t_ray_cast *ray_cast, t_player *player, float rayAngle);
int		find_vertical_hit(t_game *game, t_ray_cast *ray_cast, t_player *player, float rayAngle);

// --- // --- // --- // --- // --- //

void	render_rays(t_game *game);
void	render_player(t_game *game);
void	render_map(t_game *game);
void	update(void *param);
int		setup(t_game *game, const char *direction_input);
float	normalize_angle(float angle);
float	distance_between_points(float x1, float y1, float x2, float y2);

void	render_3d_projection(t_game *game);

// Funciones para agres sprites y texturas al juego //

#endif //CUB3D_H