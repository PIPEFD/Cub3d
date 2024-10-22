/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:24:36 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/21 14:06:06 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_rays(t_game *game)
{
	unsigned int	ray_color;
	int				i;

	ray_color = 0x38FF00FF;
	i = 50;
	while (NUM_RAYS > i)
	{
		game->draw_figures.line_params->x0 = game->player.x
			* MINIMAP_SCALE_FACTOR;
		game->draw_figures.line_params->y0 = game->player.y
			* MINIMAP_SCALE_FACTOR;
		game->draw_figures.line_params->x1 = game->rays[i].wallHitX
			* MINIMAP_SCALE_FACTOR;
		game->draw_figures.line_params->y1 = game->rays[i].wallHitY
			* MINIMAP_SCALE_FACTOR;
		game->draw_figures.line_params->color = ray_color;
		draw_line(game);
		i++;
	}
}

void	render_player(t_game *game)
{
	unsigned int	player_color;
	float			line_length;

	player_color = 0xFA0000FF;
	game->draw_figures.rect_params->x = game->player.x * MINIMAP_SCALE_FACTOR
		- (PLAYER_SIZE / 2);
	game->draw_figures.rect_params->y = game->player.y * MINIMAP_SCALE_FACTOR
		- (PLAYER_SIZE / 2);
	game->draw_figures.rect_params->width = PLAYER_SIZE;
	game->draw_figures.rect_params->height = PLAYER_SIZE;
	game->draw_figures.rect_params->color = player_color;
	draw_rectangle(game);
	game->draw_figures.line_params->x0 = game->player.x * MINIMAP_SCALE_FACTOR;
	game->draw_figures.line_params->y0 = game->player.y * MINIMAP_SCALE_FACTOR;
	line_length = 20;
	game->draw_figures.line_params->x1 = game->draw_figures.line_params->x0
		+ cos(game->player.rotationAngle) * line_length;
	game->draw_figures.line_params->y1 = game->draw_figures.line_params->y0
		+ sin(game->player.rotationAngle) * line_length;
	game->draw_figures.line_params->color = player_color;
	draw_line(game);
}

void	render_map(t_game *game)
{
	int				i;
	int				j;
	int				tile_x;
	int				tile_y;
	unsigned int	tile_color;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '0' || game->map[i][j] == ' ')
				tile_color = 0x000000FF;
			else
				tile_color = 0xE9E9E9FF;
			tile_x = j * TILE_SIZE;
			tile_y = i * TILE_SIZE;
			game->draw_figures.rect_params->x = tile_x * MINIMAP_SCALE_FACTOR;
			game->draw_figures.rect_params->y = tile_y * MINIMAP_SCALE_FACTOR;
			game->draw_figures.rect_params->width = TILE_SIZE
				* MINIMAP_SCALE_FACTOR;
			game->draw_figures.rect_params->height = TILE_SIZE
				* MINIMAP_SCALE_FACTOR;
			game->draw_figures.rect_params->color = tile_color;
			draw_rectangle(game);
		}
	}
}
