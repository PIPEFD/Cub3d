/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:56:38 by pipe              #+#    #+#             */
/*   Updated: 2024/10/22 12:42:32 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TO DO:
// Asignar variables a la estrcutura para que se puedan usar en un futuro

int	init_data_render(t_game *game, int i)
{
	// ft_memset(&game->render_params, 0, sizeof(t_render_params));
	game->render_params.perp_distance = game->rays[i].distance
		* cos(game->rays[i].rayAngle - game->player.rotationAngle);
	game->render_params.distance_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	game->render_params.wall_strip_height = (TILE_SIZE
			/ game->render_params.perp_distance)
		* game->render_params.distance_proj_plane;
	game->render_params.wall_top_pixel = (WINDOW_HEIGHT / 2)
		- (game->render_params.wall_strip_height / 2);
	game->render_params.wall_top_pixel = game->render_params.wall_top_pixel < 0 ? 0 : game->render_params.wall_top_pixel;
	game->render_params.wall_bottom_pixel = (WINDOW_HEIGHT / 2)
		+ (game->render_params.wall_strip_height / 2);
	game->render_params.wall_bottom_pixel = game->render_params.wall_bottom_pixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : game->render_params.wall_bottom_pixel;
	if (game->rays[i].wasHitVertical)
		game->render_params.wall_color = 0xffffffff;
	else
		game->render_params.wall_color = 0x000000ff;
	return (0);
}



void	render_wall_strip(t_game *game, int i)
{
	int	y;

	y = game->render_params.wall_top_pixel;
	while (y < game->render_params.wall_bottom_pixel)
	{
		mlx_put_pixel(game->img, i, y, game->render_params.wall_color);
		y++;
	}
}

void	render_floor_and_ceiling(t_game *game, int  i)
{
	int	y;

	// Renderizar techo
	y = 0;
	while (y < game->render_params.wall_top_pixel)
	{
		mlx_put_pixel(game->img, i, y, game->ceiling);
		y++;
	}
	// Renderizar suelo
	y = game->render_params.wall_bottom_pixel;
	while (y < WINDOW_HEIGHT)
	{
		mlx_put_pixel(game->img, i, y, game->floor);
		y++;
	}
}

void	render_3d_projection(t_game *game)
{
	int index_ray;

	index_ray = 0;
	while (index_ray < NUM_RAYS)
	{
		init_data_render(game, index_ray);
		render_wall_strip(game, index_ray);
		render_floor_and_ceiling(game, index_ray);
		index_ray++;
	}
	/*
	printf("// --- // --- // --- // --- // --- //\n");
	printf("\nData initialized render correctly\n");
	printf("// --- // --- // --- // --- // --- //\n");
	printf("perp_distance: %f\n", game->render_params.perp_distance);
	printf("distance_proj_plane: %f\n", game->render_params.distance_proj_plane);
	printf("wall_strip_height: %f\n", game->render_params.wall_strip_height);
	printf("wall_top_pixel: %d\n", game->render_params.wall_top_pixel);
	printf("wall_bottom_pixel: %d\n", game->render_params.wall_bottom_pixel);
	*/
}
