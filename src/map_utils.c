/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:34 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/24 17:26:13 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_has_wall_at(t_game *game, float x, float y)
{
	int		map_grid_index_x;
	int		map_grid_index_y;
	char	tile;

	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	if (map_grid_index_y < 0 || map_grid_index_y >= split_len(game->map))
		return (0);
	if (map_grid_index_x < 0 || map_grid_index_x >= (int)ft_strlen(game->map[map_grid_index_y]))
		return (0);
	tile = game->map[map_grid_index_y][map_grid_index_x];
	return (tile != '0');
}

/*
int	map_has_wall_at(t_game *game, float x, float y)
{
	int		map_grid_index_x;
	int		map_grid_index_y;
	char	tile;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
	{
		return (1);
	}
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	if (map_grid_index_y < 0 || map_grid_index_y >= MAP_NUM_ROWS
		|| map_grid_index_x < 0 || map_grid_index_x >= MAP_NUM_COLS)
	{
		return (1);
	}
	tile = game->map[map_grid_index_y][map_grid_index_x];
	return (tile != '0');
}
*/
