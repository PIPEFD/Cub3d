/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:37:35 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/31 17:09:36 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	good_rgb(char *line)
{
	int	i;
	int	num;

	i = -1;
	while (line[++i])
		if (!ft_isdigit(line[i]))
			return (printf("Error: only numbers in the RGB\n"), 0);
	num = ft_atoi(line);
	if (num > 255 || num < 0)
		return (printf("Error: only numbers betwen 0 and 255 in the RGB\n"), 0);
	return (1);
}

int	good_format(char *line)
{
	char			*temp;
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
	if (!good_rgb(red_green_blue[0]))
		return (split_free(red_green_blue), 0);
	if (!good_rgb(red_green_blue[1]))
		return (split_free(red_green_blue), 0);
	if (!good_rgb(red_green_blue[2]))
		return (split_free(red_green_blue), 0);
	split_free(red_green_blue);
	return (1);
}

int	get_ceiling(char **file, t_game *data)
{
	int		i;
	char	*temp;

	i = -1;
	while (file[++i])
	{
		temp = ft_strtrim(file[i], " ");
		if (temp)
		{
			if (!mod_strcomp(temp, "C ") && good_format(&temp[2]))
			{
				data->ceiling = get_rgb(&temp[2]);
				return (free(temp), 1);
			}
			free(temp);
		}
	}
	return (printf("Error: ceiling RGB not found\n"), 0);
}

int	get_floor(char **file, t_game *data)
{
	int		i;
	char	*temp;

	i = -1;
	while (file[++i])
	{
		temp = ft_strtrim(file[i], " ");
		if (temp)
		{
			if (!mod_strcomp(temp, "F ") && good_format(&temp[2]))
			{
				data->floor = get_rgb(&temp[2]);
				return (free(temp), 1);
			}
			free(temp);
		}
	}
	return (printf("Error: floor RGB not found\n"), 0);
}
