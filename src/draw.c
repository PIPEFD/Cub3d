/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:28:47 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/16 12:38:23 by kabasolo         ###   ########.fr       */
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

int	draw_line(t_game *game)
{
	t_line_params		*params;
	t_bresenham_vars	vars;
	int					e2;

	params = game->draw_figures.line_params;

	if (init_data_bresenham(&vars, params) != 0)
		return (-1);
	while (1)
	{
		if (vars.x0 >= 0 && vars.x0 < (int)game->img->width && vars.y0 >= 0
			&& vars.y0 < (int)game->img->height)
			mlx_put_pixel(game->img, vars.x0, vars.y0, params->color);
		if (vars.x0 == vars.x1 && vars.y0 == vars.y1)
			break ;
		e2 = 2 * vars.err;
		if (e2 >= vars.dy)
		{
			vars.err += vars.dy;
			vars.x0 += vars.sx;
		}
		if (e2 <= vars.dx)
		{
			vars.err += vars.dx;
			vars.y0 += vars.sy;
		}
	}
	return (0);
}
