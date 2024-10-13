/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:34:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/09 11:42:57 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(char **map, int x, int y)
{
	int	end;

	if (!map[y] || !map[y][x])
		return (1);
	if (map[y][x] == '1')
		return (0);
	map[y][x] = '1';
	end = 0;
	end |= flood_fill(map, x + 1, y);
	end |= flood_fill(map, x - 1, y);
	end |= flood_fill(map, x, y + 1);
	end |= flood_fill(map, x, y - 1);
	return (end);
}

int	non_valid_characters(char **map)
{
	int	y;
	int	x;

	y = -1;
	while(map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (!ft_strchr("01 NSWE", map[y][x]))
				return (1);
	}
	return (0);
}

int	everything_closed(char **map)
{
	int		y;
	int		x;
	char	**temp_map;

	temp_map = split_cpy(map);
	y = -1;
	while(temp_map[++y])
	{
		x = -1;
		while (temp_map[y][++x])
			if (ft_strchr("0NSWE", map[y][x]) && flood_fill(temp_map, x, y))
				return (split_free(temp_map), 1);
	}
	return (split_free(temp_map), 0);
}

void	get_rgb(int red_green_blue, char *rgb)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	
}

void	get_filenames(t_data	*data, char **file)
{
	int	i;

	i = -1;
	while (file[++i])
	{
		if (data->north_file && data->south_file)
			if (data->west_file && data->east_file)
				if (data->floor[0] >= 0 && data->ceiling[0] == -1)
					return (get_map(data, &file[i]), NULL);
		if (!data->north_file && ft_strcmp(file[i], "NO "))
			data->north_file = ft_strdup(&file[i][3]);
		if (!data->south_file && ft_strcmp(file[i], "SO "))
			data->south_file = ft_strdup(&file[i][3]);
		if (!data->west_file && ft_strcmp(file[i], "WE "))
			data->west_file = ft_strdup(&file[i][3]);
		if (!data->east_file && ft_strcmp(file[i], "EA "))
			data->east_file = ft_strdup(&file[i][3]);
		if (data->floor[0] == -1 && t_strcmp(file[i], "F "))
			get_rgb(data->floor, &file[i][3]);
		if (data->ceiling[0] == -1 && t_strcmp(file[i], "C "))
			get_rgb(data->ceiling, &file[i][3]);
	}
}

int	get_map(t_data	*data, char *file_name)
{
	char *the_whole_file;
	char *file;

	the_whole_file = read_the_file(file_name);
	file = ft_split(the_whole_file, '\n');
	get_files(data, file);
	if (!get_sprites(data))
		return (0);
	free(the_whole_file);
	return (1);
}

int	valid_map(t_data	*data)
{
	if (non_valid_characters(data->map))
		return (0);
	if (!everything_closed(data->map))
		return (0);
}

int	get_player_data(t_data	*data)
{
	int	y;
	int	x;

	y = -1;
	while(data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (ft_strchr("NSWE", data->map[y][x]))
			{
				if (data->dir != -1)
					return (1);
				data->px = x;
				data->py = y;
				data->dir = data->map[y][x];
			}
		}
	}
	return (0);
}

t_data	*parsing(char *file_name)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!get_map(data, file_name))
		return(free_data(data), NULL);
	if (!valid_map(data->map))
		return (free_data(data), NULL);
	if (!get_player_data(data))
		return (free_data(data), NULL);
	return (data);
}