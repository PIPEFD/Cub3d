/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:12:03 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/30 14:42:31 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_filename(char **file, char *id)
{
	int		i;
	char	*temp1;
	char	*temp2;
	char	*res;

	i = -1;
	while (file[++i])
	{
		temp1 = ft_strtrim(file[i], " ");
		if (!mod_strcomp(temp1, id))
		{
			temp2 = ft_strtrim(&file[i][3], " ");
			res = ft_strdup(temp2);
			return (free(temp1), free(temp2), res);
		}
		free(temp1);
	}
	return (NULL);
}

unsigned int	get_rgb(char *line)
{
	char			*temp;
	unsigned char	rgb[3];
	char			**red_green_blue;

	red_green_blue = ft_split(line, ',');
	if (split_len(red_green_blue) != 3)
		return (split_free(red_green_blue), 0);
	temp = ft_strtrim(red_green_blue[0], " ");
	free(red_green_blue[0]);
	red_green_blue[0] = temp;
	temp = ft_strtrim(red_green_blue[1], " ");
	free(red_green_blue[1]);
	red_green_blue[1] = temp;
	temp = ft_strtrim(red_green_blue[2], " ");
	free(red_green_blue[2]);
	red_green_blue[2] = temp;
	rgb[0] = (unsigned char)ft_atoi(red_green_blue[0]);
	rgb[1] = (unsigned char)ft_atoi(red_green_blue[1]);
	rgb[2] = (unsigned char)ft_atoi(red_green_blue[2]);
	split_free(red_green_blue);
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
}

int	get_ceiling(char **file, t_game *data)
{
	int	i;
	char	*temp;

	i = -1;
	while (file[++i])
	{
		temp = ft_strtrim(file[i], " ");
		if (temp)
		{
			if (!mod_strcomp(temp, "C "))
			{
				data->ceiling = get_rgb(&temp[2]);
				return (free(temp), 1);
			}
			free(temp);
		}
	}
	return (0);
}

int	get_floor(char **file, t_game *data)
{
	int	i;
	char	*temp;

	i = -1;
	while (file[++i])
	{
		temp = ft_strtrim(file[i], " ");
		if (temp)
		{
			if (!mod_strcomp(temp, "F "))
			{
				data->floor = get_rgb(&temp[2]);
				return (free(temp), 1);
			}
			free(temp);
		}
	}
	return (0);
}

int	get_file_data(t_game *data, char *file_name)
{
	char	*the_whole_file;
	char	**file;

	the_whole_file = read_the_file(file_name);
	if (!the_whole_file)
		return (0);
	file = ft_split(the_whole_file, '\n');
	free(the_whole_file);
	data->no->file = get_filename(file, "NO ");
	data->so->file = get_filename(file, "SO ");
	data->we->file = get_filename(file, "WE ");
	data->ea->file = get_filename(file, "EA ");
	if (!data->no->file || !data->so->file)
		return (split_free(file), 0);
	if (!data->we->file || !data->ea->file)
		return (split_free(file), 0);
	if (!get_floor(file, data))
		return (split_free(file), 0);
	if (!get_ceiling(file, data))
		return (split_free(file), 0);
	if (!get_map(data, file))
		return (split_free(file), 0);
	split_free(file);
	return (1);
}

void	get_map_data(t_game *game)
{
	int	i;

	i = -1;
	game->width = 0;
	while (game->map[++i])
		if (game->width < ft_strlen(game->map[i]) * TILE_SIZE)
			game->width = ft_strlen(game->map[i]) * TILE_SIZE;
	game->heigth = split_len(game->map) * TILE_SIZE;
}
