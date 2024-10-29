/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:34 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/29 16:51:04 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_has_wall_at(t_game *game, float x, float y)
{
	int		map_grid_index_x;
	int		map_grid_index_y;
	char	tile;

	map_grid_index_x = ((int)x / TILE_SIZE);
	map_grid_index_y = ((int)y / TILE_SIZE);
	if (map_grid_index_y < 0 || map_grid_index_y >= split_len(game->map))
		return (0);
	if (map_grid_index_x < 0
		|| map_grid_index_x >= (int)ft_strlen(game->map[map_grid_index_y]))
		return (0);
	tile = game->map[map_grid_index_y][map_grid_index_x];
	return (tile != '0');
}

int	valid_map(char **map)
{
	if (non_valid_characters(map))
		return (0);
	if (!everything_closed(map))
		return (0);
	return (1);
}

int	get_map(t_game *data, char **file)
{
	int	y;
	int	x;

	y = split_len(file);
	while (--y >= 0)
	{
		x = 0;
		while (file[y][x] && ft_strchr("01 NSWE", file[y][x]))
			x++;
		if (!ft_strchr("01 NSWE", file[y][x]))
			break ;
	}
	data->map = split_cpy(&file[y + 1]);
	return (!(!data->map));
}

int	everything_closed(char **map)
{
	int		y;
	int		x;
	char	**temp_map;

	y = -1;
	temp_map = split_cpy(map);
	y = -1;
	while (temp_map[++y])
	{
		x = -1;
		while (temp_map[y][++x])
			if (ft_strchr("0NSWE", map[y][x]) && flood_fill(temp_map, x, y))
				return (split_free(temp_map), 0);
	}
	return (split_free(temp_map), 1);
}

int	non_valid_characters(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (!ft_strchr("01 NSWE", map[y][x]))
				return (1);
	}
	return (0);
}
