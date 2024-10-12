/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:26:06 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/12 23:15:10 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	normalizeAngle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
	{
		angle = TWO_PI + angle;
	}
	return (angle);
}

float	distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

