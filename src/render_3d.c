/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:56:38 by pipe              #+#    #+#             */
/*   Updated: 2024/10/28 14:24:03 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_strip(t_game *game, int x)
{
	int	y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
		mlx_put_pixel(game->img, x, y, game->strip[y]);
}

void	get_strip(t_game *game, t_texture *text, int x)
{
	int	y;
	int	anti_y;
	int	img_x;
	int	img_y;

	y = 0;
	while (y < game->render_params.wall_top_pixel)
		game->strip[y++] = game->ceiling;
	img_x = 1;
	if (x != 1)
		img_x = (x * text->width2) / TILE_SIZE;
	anti_y = y;
	if (game->render_params.wall_top_pixel < 0)
		anti_y += game->render_params.wall_top_pixel;
	while (y++ < game->render_params.wall_bottom_pixel && y < WINDOW_HEIGHT)
	{
		img_y = ((y - anti_y) * text->height)
			/ (game->render_params.wall_bottom_pixel
				- game->render_params.wall_top_pixel);
		if (img_y >= 0 && img_y < text->height && img_x >= 0
			&& img_x < text->width2)
			game->strip[y] = text->img[img_y][img_x];
	}
	while (y < WINDOW_HEIGHT)
		game->strip[y++] = game->floor;
}

void	render(t_game *game, int i)
{
	if (!game->rays[i].washitvertical)
	{
		if (game->rays[i].rayangle < PI && game->rays[i].rayangle > 0)
			get_strip(game, game->no, (int)(game->rays[i].wallhitx
					+ game->rays[i].wallhity) % TILE_SIZE);
		else
			get_strip(game, game->so, TILE_SIZE - 1
				- ((int)(game->rays[i].wallhitx + game->rays[i].wallhity)
					% TILE_SIZE));
	}
	else
	{
		if (game->rays[i].rayangle > PI * 1 / 2 && game->rays[i].rayangle < PI
			* 3 / 2)
			get_strip(game, game->we, TILE_SIZE - 1
				- ((int)(game->rays[i].wallhitx + game->rays[i].wallhity)
					% TILE_SIZE));
		else
			get_strip(game, game->ea, (int)(game->rays[i].wallhitx
					+ game->rays[i].wallhity) % TILE_SIZE);
	}
}

int	init_data_render(t_game *game, int i)
{
	if(game->rays[i].distance == 0)
		game->rays[i].distance = 0.1;
	game->render_params.perp_distance = game->rays[i].distance
		* cos(game->rays[i].rayangle - game->player.rotationangle);
	game->render_params.distance_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	game->render_params.wall_strip_height = (TILE_SIZE
			/ game->render_params.perp_distance)
		* game->render_params.distance_proj_plane;
	game->render_params.wall_top_pixel = (WINDOW_HEIGHT / 2)
		- (game->render_params.wall_strip_height / 2);
	game->render_params.wall_bottom_pixel = (WINDOW_HEIGHT / 2)
		+ (game->render_params.wall_strip_height / 2);
	return (0);
}

void	render_3d_projection(t_game *game)
{
	int	index_ray;

	index_ray = -1;
	while (++index_ray < NUM_RAYS)
	{
		init_data_render(game, index_ray);
		render(game, index_ray);
		render_strip(game, index_ray);
	}
}
