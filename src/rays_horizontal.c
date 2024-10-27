/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/27 15:26:14 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_horizontal_ray(t_ray_cast *ray_cast, t_player *player,
		float rayAngle)
{
	ray_cast->foundHorzWallhit = 0;
	ray_cast->horWallHitX = 0;
	ray_cast->horWallHitY = 0;
	ray_cast->horWallContent = 0;
	ray_cast->yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
	if (ray_cast->isRayFacingDown)
		ray_cast->yintercept += TILE_SIZE;
	ray_cast->xintercept = player->x + (ray_cast->yintercept - player->y)
		/ tan(rayAngle);
	ray_cast->ystep = TILE_SIZE;
	if (ray_cast->isRayFacingUp)
		ray_cast->ystep *= -1;
	ray_cast->xstep = TILE_SIZE / tan(rayAngle);
	if (ray_cast->isRayFacingLeft && ray_cast->xstep > 0)
		ray_cast->xstep *= -1;
	else if (ray_cast->isRayFacingRight && ray_cast->xstep < 0)
		ray_cast->xstep *= -1;
	ray_cast->nextHorzTouchX = ray_cast->xintercept;
	ray_cast->nextHorzTouchY = ray_cast->yintercept;
}

void	find_horizontal_hit(t_game *game, t_ray_cast *ray_cast,
		t_player *player, float rayAngle)
{
	float	xtocheck;
	float	ytocheck;

	initialize_horizontal_ray(ray_cast, player, rayAngle);
	while (ray_cast->nextHorzTouchX >= 0
		&& ray_cast->nextHorzTouchX <= game->width
		&& ray_cast->nextHorzTouchY >= 0
		&& ray_cast->nextHorzTouchY <= game->heigth)
	{
		xtocheck = ray_cast->nextHorzTouchX;
		ytocheck = ray_cast->nextHorzTouchY;
		if (ray_cast->isRayFacingUp)
			ytocheck -= 1;
		if (map_has_wall_at(game, xtocheck, ytocheck))
		{
			ray_cast->horWallHitX = ray_cast->nextHorzTouchX;
			ray_cast->horWallHitY = ray_cast->nextHorzTouchY;
			ray_cast->horWallContent = game->map[(int)floor(ytocheck
					/ TILE_SIZE)][(int)floor(xtocheck / TILE_SIZE)];
			ray_cast->foundHorzWallhit = 1;
			break ;
		}
		ray_cast->nextHorzTouchX += ray_cast->xstep;
		ray_cast->nextHorzTouchY += ray_cast->ystep;
	}
}
