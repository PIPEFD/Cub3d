/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/12 00:21:06 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void updateRayProperties(t_ray* ray, t_ray_cast* ray_cast, float rayAngle) {
    ray->rayAngle = rayAngle;
    ray->isRayFacingDown = ray_cast->isRayFacingDown;
    ray->isRayFacingUp = ray_cast->isRayFacingUp;
    ray->isRayFacingLeft = ray_cast->isRayFacingLeft;
    ray->isRayFacingRight = ray_cast->isRayFacingRight;
}

void	cast_ray(t_game *game, float ray_angle, int stripid)
{
	t_player	*player;
	t_ray		*ray;
	t_ray_cast	*ray_cast;

	ray_angle = normalizeAngle(ray_angle);
	player = &game->player;
	ray = &game->rays[stripid];
	ray_cast = &game->ray_casts[stripid];
	determineRayDirection(ray_cast, ray_angle);
	castHorizontalRay(game, ray_cast, ray_angle);
	castVerticalRay(game, ray_cast, ray_angle);
	calculateDistances(ray_cast, player);
	determineClosestHit(ray_cast, ray);
	updateRayProperties(ray, ray_cast, ray_angle);
}

void	cast_all_rays(t_game *game)
{
	float	rayangle;
	int		stripid;

	stripid = 0;
	rayangle = game->player.rotationAngle - (FOV / 2);
	while (stripid++ < NUM_RAYS)
	{
		cast_ray(game, rayangle, stripid);
		rayangle += FOV / NUM_RAYS;
	}
}
