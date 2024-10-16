/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:34:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/16 11:44:42 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	flood_fill(char **map, int x, int y)
{
	int	end;

	if (!map[y] || !map[y][x] || map[y][x] == ' ')
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

int	valid_map(t_data	*data)
{
	if (non_valid_characters(data->map))
		return (0);
	if (!everything_closed(data->map))
		return (0);
}

int	get_map(t_data	*data, char **file)
{
	int	len;
	int	y;
	int	x;

	len = split_len(file);
	y = len;
	while (file[--y])
	{
		x = -1;
		while (file[y][++x])
			if (!ft_strchr("01 NSWE", file[y][x]))
				break;
	}
	data->map = split_cpy(&file[y + 1]);
	return (!(!data->map));
}

int	get_rgb(char *rgb)
{
	unsigned char	rgb[3];
	char			**red_green_blue;

	red_green_blue = ft_split(rgb, ',');
	if (split_len(red_green_blue) != 3)
		return (0);
	if (!isnum(red_green_blue[0]) || \
		!isnum(red_green_blue[1]) || \
		!isnum(red_green_blue[2]))
		return (0);
	rgb[0] = (unsigned char)ft_atoi(red_green_blue[0]);
	rgb[1] = (unsigned char)ft_atoi(red_green_blue[1]);
	rgb[2] = (unsigned char)ft_atoi(red_green_blue[2]);
	return (0 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

int	get_filenames(t_data	*data, char **file)
{
	if (!file || !file[0])
		return (1)
	if ((data->no->file && !ft_strcmp(file[0], "NO ")) || \
		(data->so->file && !ft_strcmp(file[0], "SO ")) || \
		(data->we->file && !ft_strcmp(file[0], "WE ")) || \
		(data->ea->file && !ft_strcmp(file[0], "EA ")) || \
		(data->floor[0] == -1 && !ft_strcmp(file[0], "F ")) || \
		(data->ceiling[0] == -1 && !ft_strcmp(file[0], "C ")))
		return (0);
	if (!ft_strcmp(file[0], "NO "))
		data->no->file = ft_strdup(&file[0][3]);
	else if (!ft_strcmp(file[0], "SO "))
		data->so->file = ft_strdup(&file[0][3]);
	else if (!ft_strcmp(file[0], "WE "))
		data->we->file = ft_strdup(&file[0][3]);
	else if (!ft_strcmp(file[0], "EA "))
		data->ea->file = ft_strdup(&file[0][3]);
	else if (!ft_strcmp(file[0], "F "))
		data->floor = get_rgb(&file[0][3]);
	else if (!ft_strcmp(file[0], "C "))
		data->ceiling = get_rgb(&file[0][3]);
	return (get_filenames(data, &file[1]));
}

int	get_sprites(t_data	*data, int x, int y)
{
	data->no->img = mlx_xpm_file_to_image(game->mlx, data->no->file, &x, &y);
	data->so->img = mlx_xpm_file_to_image(game->mlx, data->so->file, &x, &y);
	data->we->img = mlx_xpm_file_to_image(game->mlx, data->we->file, &x, &y);
	data->ea->img = mlx_xpm_file_to_image(game->mlx, east->so->file, &x, &y);
	return (data->no->img && data->so->img && data->we->img && data->ea->img);
}

int	get_file_data(t_data	*data, char *file_name)
{
	char *the_whole_file;
	char *file;

	the_whole_file = read_the_file(file_name);
	file = ft_split(the_whole_file, '\n');
	free(the_whole_file);
	if (!get_filenames(data, file))
		return (free(file), 0);
	if (!get_map(data, file))
		return (free(file), 0);
	free(file);
	if (!get_sprites(data, 0, 0))
		return (0);
	return (1);
}

void	init_data(t_data	*data)
{
	data->dir = -1;
	data->no->file = NULL;
	data->so->file = NULL;
	data->ea->file = NULL;
	data->we->file = NULL;
	data->no->img = NULL;
	data->so->img = NULL;
	data->ea->img = NULL;
	data->we->img = NULL;
	data->ceiling = 0;
	data->floor = 0;
	data->map = NULL;
}

t_data	*parsing(char *file_name)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	init_data(data);
	if (!get_file_data(data, file_name))
		return(free_data(data), NULL);
	if (!valid_map(data->map))
		return (free_data(data), NULL);
	if (!get_player_data(data))
		return (free_data(data), NULL);
	return (data);
}
