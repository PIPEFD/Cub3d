/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/21 11:57:39 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_vertical_hit(t_game *game, t_ray_cast *ray_cast, t_player *player,
		float rayAngle)
{
	float	xToCheck;
	float	yToCheck;

	ray_cast->foundVerWallhit = 0;
	ray_cast->verWallHitX = 0;
	ray_cast->verWallHitY = 0;
	ray_cast->verWallContent = 0;
	ray_cast->xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
	ray_cast->xintercept += ray_cast->isRayFacingRight ? TILE_SIZE : 0;
	ray_cast->yintercept = player->y + (ray_cast->xintercept - player->x)
		* tan(rayAngle);
	ray_cast->xstep = TILE_SIZE;
	ray_cast->xstep *= ray_cast->isRayFacingLeft ? -1 : 1;
	ray_cast->ystep = TILE_SIZE * tan(rayAngle);
	ray_cast->ystep *= (ray_cast->isRayFacingUp && ray_cast->ystep > 0) ?
		-1 : 1;
	ray_cast->ystep *= (ray_cast->isRayFacingDown && ray_cast->ystep < 0) ?
		-1 : 1;
	ray_cast->nextVerTouchX = ray_cast->xintercept;
	ray_cast->nextVerTouchY = ray_cast->yintercept;
	while (ray_cast->nextVerTouchX >= 0
		&& ray_cast->nextVerTouchX <= game->width
		&& ray_cast->nextVerTouchY >= 0
		&& ray_cast->nextVerTouchY <= game->heigth)
	{
		xToCheck = ray_cast->nextVerTouchX + (ray_cast->isRayFacingLeft ?
				-1 : 0);
		yToCheck = ray_cast->nextVerTouchY;
		if (map_has_wall_at(game, xToCheck, yToCheck))
		{
			ray_cast->verWallHitX = ray_cast->nextVerTouchX;
			ray_cast->verWallHitY = ray_cast->nextVerTouchY;
			ray_cast->verWallContent = game->map[(int)floor(yToCheck
					/ TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			ray_cast->foundVerWallhit = 1;
			break ;
		}
		else
		{
			ray_cast->nextVerTouchX += ray_cast->xstep;
			ray_cast->nextVerTouchY += ray_cast->ystep;
		}
	}
	return (0);
}
