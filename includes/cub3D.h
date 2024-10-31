/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:33:21 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/31 16:46:02 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "structs.h"

int				parsing(t_game *game, char *file_name);
// Funciones de parseo y estrucuturacion del mapa //
// --- // --- // --- // --- // --- //
// Funciones para la inicializacion de la estructura
// --- // --- // --- // --- // --- //
// --- // --- // --- // --- // --- //
void			init_data(t_game *data);
int				init_data_all(t_game *game);
int				init_data_map(t_game *game);
void			init_data_player(t_game *game);
void			init_data_rays(t_game *game);
int				init_data_figures(t_game *game);
int				init_data_render(t_game *game, int i);

// --- // --- // --- // --- // --- //

// get file data

void			get_rgbs(char **file, t_game *data);
int				get_file_data(t_game *data, char *file_name);
void			get_map_data(t_game *game);
char			*get_filename(char **file, char *id);
uint32_t		get_color(uint8_t *p);
unsigned int	get_rgb(char *line);
int				get_sprites(t_game *data);
int				load_sprite(t_texture *text, int x, int y);
char			*read_the_file(char *file_name);

// --- // --- // --- // --- // --- //

// Funciones para setear la dirección del jugador

// --- // --- // --- // --- // --- //
void			set_player_direction(t_player *player);
// Añadido

// --- // --- // --- // --- // --- //
// Function for update postion of player position
void			move_player(t_game *game, t_player *player);
int				get_player_data(t_game *data);

// --- // --- // --- // --- // --- //

// --- // --- // --- // --- // --- //
/*FUNCIONES PARA GENERA EL RAYCASTING EN MLX Y RENDERIZAR EL MAPA
LOS RAYOS CON BASE EN LA POSICIÓN DEL JUGADOR...*/
// --- // --- // --- // --- // --- // // --- // --- // --- // --- // --- //
// Function for draw a rectangle form in mlx

/* --- // --- // --- // --- // --- //
	Funcion para dibujar una linea recta en mlx con base en el
	// algoritmo de bresenham
// --- // --- // --- // --- // --- */
int				draw_line(t_game *game);

/* --- // --- // --- // --- // --- //
	Funcion para dibujar un rectangulo en mlx
// --- // --- // --- // --- // --- */
int				draw_rectangle(t_game *game);

// void					draw_rectangle(mlx_image_t *img, int x, int y,
// 							int width, int height, uint32_t color);

// // Fuunction for draw a line in mlx
// void					draw_line(mlx_image_t *img, int x0, int y0, int x1,
// 							int y1, uint32_t color);

void			destroy_window(t_game *game);

void			key_hook(mlx_key_data_t keydata, void *param);

// FLood fill algorithm
int				flood_fill(char **map, int x, int y);

// Funciones para el mapa 2D //
// -- // -- // --- // -- //
int				get_map(t_game *data, char **file);
int				valid_map(t_game *game);
int				non_valid_characters(char **map);
int				everything_closed(char **map);
int				player_wall(t_game *game, float x, float y);
int				map_has_wall_at(t_game *game, float x, float y);
int				get_ceiling(char **file, t_game *data);
int				get_floor(char **file, t_game *data);
// --- // --- // --- // --- // --- //
// Funciones para determinar la poscionde del rayo en un plano 2D
// Ademas de Funciones auxiliares para realizar el calculo
// de la vista a la cual se dirijean los rayos ademas
// de las intercepciones para determinar el chocque de los rayos
// con los muros en el angulo de vision establecido
// --- // --- // --- // --- // --- //

// void					cast_ray(t_game *game, float rayAngle, int stripid);

int				initialize_ray(t_game *game, float *rayAngle, int stripid);
int				calculate_hit_distances(t_game *game, t_ray_cast *ray_cast,
					int stripid);
int				assign_ray_properties(t_game *game, float rayAngle,
					int stripid);

void			cast_all_rays(t_game *game);
int				cast_ray_setup(t_game *game, float rayAngle, int stripid);
void			find_horizontal_hit(t_game *game, t_ray_cast *ray_cast,
					t_player *player, float rayAngle);
void			find_vertical_hit(t_game *game, t_ray_cast *ray_cast,
					t_player *player, float rayAngle);

// --- // --- // --- // --- // --- //

void			render_minimap(t_game *game);
// void	render_rays(t_game *game);
void			update(void *param);
int				setup(t_game *game);
float			normalize_angle(float angle);
float			distance_between_points(float x1, float y1, float x2, float y2);

void			render_3d_projection(t_game *game);

// Funciones para la lectura de archivos y manejo de strings //
char			*mod_join(char *s1, char *s2);
int				mod_strcomp(char *s1, char *s2);

// Utils.c
int				ft_abs(int n);

void			free_sprite(t_texture *text);
void			free_texture(t_texture **texture);
void			destroy_window(t_game *game);
void			destroy_window2(t_game *game);
void			destroy_window3(t_game *game);
void			destroy_window4(t_game *game);

// Funciones para agres sprites y texturas al juego //

#endif // CUB3D_H