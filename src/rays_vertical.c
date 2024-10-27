/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/27 15:23:30 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_vertical_ray(t_ray_cast *ray_cast, t_player *player,
		float rayAngle)
{
	ray_cast->foundVerWallhit = 0;
	ray_cast->verWallHitX = 0;
	ray_cast->verWallHitY = 0;
	ray_cast->verWallContent = 0;
	ray_cast->xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
	if (ray_cast->isRayFacingRight)
		ray_cast->xintercept += TILE_SIZE;
	ray_cast->yintercept = player->y + (ray_cast->xintercept - player->x)
		* tan(rayAngle);
	ray_cast->xstep = TILE_SIZE;
	if (ray_cast->isRayFacingLeft)
		ray_cast->xstep *= -1;
	ray_cast->ystep = TILE_SIZE * tan(rayAngle);
	if (ray_cast->isRayFacingUp && ray_cast->ystep > 0)
		ray_cast->ystep *= -1;
	else if (ray_cast->isRayFacingDown && ray_cast->ystep < 0)
		ray_cast->ystep *= -1;
	ray_cast->nextVerTouchX = ray_cast->xintercept;
	ray_cast->nextVerTouchY = ray_cast->yintercept;
}

void	find_vertical_hit(t_game *game, t_ray_cast *ray_cast, t_player *player,
		float rayAngle)
{
	float	xtocheck;
	float	ytocheck;

	initialize_vertical_ray(ray_cast, player, rayAngle);
	while (ray_cast->nextVerTouchX >= 0
		&& ray_cast->nextVerTouchX <= game->width
		&& ray_cast->nextVerTouchY >= 0
		&& ray_cast->nextVerTouchY <= game->heigth)
	{
		xtocheck = ray_cast->nextVerTouchX;
		if (ray_cast->isRayFacingLeft)
			xtocheck -= 1;
		ytocheck = ray_cast->nextVerTouchY;
		if (map_has_wall_at(game, xtocheck, ytocheck))
		{
			ray_cast->verWallHitX = ray_cast->nextVerTouchX;
			ray_cast->verWallHitY = ray_cast->nextVerTouchY;
			ray_cast->verWallContent = game->map[(int)floor(ytocheck
					/ TILE_SIZE)][(int)floor(xtocheck / TILE_SIZE)];
			ray_cast->foundVerWallhit = 1;
			break ;
		}
		ray_cast->nextVerTouchX += ray_cast->xstep;
		ray_cast->nextVerTouchY += ray_cast->ystep;
	}
}
