/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:28:47 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/27 13:07:43 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_rectangle(t_game *game)
{
	t_rectangle_params	*params;
	int					i;
	int					j;

	params = game->draw_figures.rect_params;
	i = params->x;
	while (i < (params->x + params->width))
	{
		j = params->y;
		while (j < (params->y + params->height))
		{
			if (i >= 0 && i < (int)game->img->width && j >= 0
				&& j < (int)game->img->height)
				mlx_put_pixel(game->img, i, j, params->color);
			j++;
		}
		i++;
	}
	return (0);
}
