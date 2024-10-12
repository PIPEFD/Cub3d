/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:26:06 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/12 00:25:09 by pipe             ###   ########.fr       */
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

int	determineRayDirection(t_ray_cast *ray_cast, float rayAngle)
{
	ray_cast->isRayFacingDown = rayAngle > 0 && rayAngle < PI;
	ray_cast->isRayFacingUp = !ray_cast->isRayFacingDown;
	ray_cast->isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
	ray_cast->isRayFacingLeft = !ray_cast->isRayFacingRight;
	return (0);
}

void	calculateDistances(t_ray_cast *ray_cast, t_player *player)
{
	ray_cast->horHitDistance = ray_cast->foundHorzWallhit ? distanceBetweenPoints(player->x,
			player->y, ray_cast->horWallHitX, ray_cast->horWallHitY) : FLT_MAX;
	ray_cast->verHitDistance = ray_cast->foundVerWallhit ? distanceBetweenPoints(player->x,
			player->y, ray_cast->verWallHitX, ray_cast->verWallHitY) : FLT_MAX;
}

void	determineClosestHit(t_ray_cast *ray_cast, t_ray *ray)
{
	if (ray_cast->verHitDistance < ray_cast->horHitDistance)
	{
		ray->distance = ray_cast->verHitDistance;
		ray->wallHitX = ray_cast->verWallHitX;
		ray->wallHitY = ray_cast->verWallHitY;
		ray->wallHitContent = ray_cast->verWallContent;
		ray->wasHitVertical = 1;
	}
	else
	{
		ray->distance = ray_cast->horHitDistance;
		ray->wallHitX = ray_cast->horWallHitX;
		ray->wallHitY = ray_cast->horWallHitY;
		ray->wallHitContent = ray_cast->horWallContent;
		ray->wasHitVertical = 0;
	}
}
