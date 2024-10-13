/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:56:38 by pipe              #+#    #+#             */
/*   Updated: 2024/10/14 00:59:44 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
// TO DO:
// Asignar variables a la estrcutura para que se puedan usar en un futuro
void	calculate_projection(t_game *game, int i, float *perp_distance,
		float *distance_proj_plane, float *wall_strip_height,
		int *wall_top_pixel, int *wall_bottom_pixel, unsigned int *wall_color)
{
	*perp_distance = game->rays[i].distance * cos(game->rays[i].rayAngle
			- game->player.rotationAngle);
	*distance_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	*wall_strip_height = (TILE_SIZE / *perp_distance) * *distance_proj_plane;
	*wall_top_pixel = (WINDOW_HEIGHT / 2) - (*wall_strip_height / 2);
	*wall_top_pixel = *wall_top_pixel < 0 ? 0 : *wall_top_pixel;
	*wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (*wall_strip_height / 2);
	*wall_bottom_pixel = *wall_bottom_pixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : *wall_bottom_pixel;
	if (game->rays[i].wasHitVertical)
		*wall_color = 0xFFFFFFFF;
	else
		*wall_color = 0xCCCCCCFF;
}

void	render_wall_strip(t_game *game, int i, int wall_top_pixel,
		int wall_bottom_pixel, unsigned int wall_color)
{
	int	y;

	y = wall_top_pixel;
	while (y < wall_bottom_pixel)
	{
		mlx_put_pixel(game->img, i, y, wall_color);
		y++;
	}
}

void	render_floor_and_ceiling(t_game *game, int i, int wall_top_pixel,
		int wall_bottom_pixel)
{
	int	y;

	// Renderizar techo
	y = 0;
	while (y < wall_top_pixel)
	{
		mlx_put_pixel(game->img, i, y, 0x000000FF);
		y++;
	}
	// Renderizar suelo
	y = wall_bottom_pixel;
	while (y < WINDOW_HEIGHT)
	{
		mlx_put_pixel(game->img, i, y, 0x7F7F7FFF);
		y++;
	}
}

void	render_3d_projection(t_game *game)
{
	float			perp_distance;
	float			distance_proj_plane;
	float			wall_strip_height;
	int				wall_top_pixel;
	int				wall_bottom_pixel;
	unsigned int	wall_color;
	int				i;

	i = 0;
	while (i < NUM_RAYS)
	{
		calculate_projection(game, i, &perp_distance, &distance_proj_plane,
			&wall_strip_height, &wall_top_pixel, &wall_bottom_pixel,
			&wall_color);
		render_wall_strip(game, i, wall_top_pixel, wall_bottom_pixel,
			wall_color);
		render_floor_and_ceiling(game, i, wall_top_pixel, wall_bottom_pixel);
		i++;
	}
}
