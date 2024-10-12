/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:24:36 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/13 01:01:08 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	render_rays(t_game *game)
{
	unsigned int	ray_color;
	int				i;

	i = 50;
	ray_color = 0x38FF00FF;
	while (i < NUM_RAYS)
	{
		draw_line(game->img, game->player.x * MINIMAP_SCALE_FACTOR,
			game->player.y * MINIMAP_SCALE_FACTOR, game->rays[i].wallHitX
			* MINIMAP_SCALE_FACTOR, game->rays[i].wallHitY
			* MINIMAP_SCALE_FACTOR, ray_color);
		i++;
	}
}

void	render_player(t_game *game)
{
	unsigned int	player_color;

	player_color = 0xFA0000FF;
	draw_rectangle(game->img, game->player.x * MINIMAP_SCALE_FACTOR,
		game->player.y * MINIMAP_SCALE_FACTOR, game->player.width
		* MINIMAP_SCALE_FACTOR, game->player.height * MINIMAP_SCALE_FACTOR,
		player_color);
	draw_line(game->img, game->player.x * MINIMAP_SCALE_FACTOR, game->player.y
		* MINIMAP_SCALE_FACTOR, (game->player.x
			+ cos(game->player.rotationAngle) * 40) * MINIMAP_SCALE_FACTOR,
		(game->player.y + sin(game->player.rotationAngle) * 40)
		* MINIMAP_SCALE_FACTOR, player_color);
}

int	render_map(t_game *game)
{
	int				i;
	int				j;
	int				tile_x;
	int				tile_y;
	unsigned int	tile_color;

	i = 0;
	j = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			tile_x = j * TILE_SIZE;
			tile_y = i * TILE_SIZE;
			if (game->map[i][j] != '0')
				tile_color = 0xE9E9E9FF;
			else
				tile_color = 0x000000FF;
			draw_rectangle(game->img, tile_x * MINIMAP_SCALE_FACTOR, tile_y
				* MINIMAP_SCALE_FACTOR, TILE_SIZE * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR, tile_color);
			j++;
		}
		i++;
	}
	return (0);
}
