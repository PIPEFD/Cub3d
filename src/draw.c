/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:28:47 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/13 18:12:55 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_rectangle(mlx_image_t *img, int x, int y, int width, int height,
					unsigned int color)
{
	for (int i = x; i < x + width; i++)
	{
		for (int j = y; j < y + height; j++)
		{
			if (i >= 0 && i < (int)img->width && j >= 0 && j < (int)img->height)
				mlx_put_pixel(img, i, j, color);
		}
	}
}

void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1,
			   unsigned int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;

	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = (x0 < x1) - (x0 >= x1);
	sy = (y0 < y1) - (y0 >= y1);
	err = dx + dy;
	while (1)
	{
		if (x0 >= 0 && x0 < (int)img->width && y0 >= 0 && y0 < (int)img->height)
			mlx_put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
// TO DO:
/*Crear estrucutra para funciones 3d ademas de estrucutra para funciones de dibujo necesarias para generarr el mapa

*/
