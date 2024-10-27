/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/27 14:45:59 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	initialize_ray(t_game *game, float *rayAngle, int stripid)
{
	t_ray_cast	*ray_cast;

	*rayAngle = normalize_angle(*rayAngle);
	ray_cast = &game->ray_casts[stripid];
	ray_cast->isRayFacingDown = (*rayAngle > 0 && *rayAngle < PI);
	ray_cast->isRayFacingUp = !ray_cast->isRayFacingDown;
	ray_cast->isRayFacingRight = (*rayAngle < 0.5 * PI || *rayAngle > 1.5 * PI);
	ray_cast->isRayFacingLeft = !ray_cast->isRayFacingRight;
	return (0);
}

void	set_hit_distances(t_game *game, t_ray_cast *ray_cast)
{
	t_player	*player;

	player = &game->player;
	if (ray_cast->foundHorzWallhit)
		ray_cast->horHitDistance = distance_between_points(player->x, player->y,
				ray_cast->horWallHitX, ray_cast->horWallHitY);
	else
		ray_cast->horHitDistance = FLOAT_MAX;
	if (ray_cast->foundVerWallhit)
		ray_cast->verHitDistance = distance_between_points(player->x, player->y,
				ray_cast->verWallHitX, ray_cast->verWallHitY);
	else
		ray_cast->verHitDistance = FLOAT_MAX;
}

int	calculate_hit_distances(t_game *game, t_ray_cast *ray_cast, int stripid)
{
	t_ray	*rays;

	rays = game->rays;
	set_hit_distances(game, ray_cast);
	if (ray_cast->verHitDistance < ray_cast->horHitDistance)
	{
		rays[stripid].distance = ray_cast->verHitDistance;
		rays[stripid].wallHitX = ray_cast->verWallHitX;
		rays[stripid].wallHitY = ray_cast->verWallHitY;
		rays[stripid].wallHitContent = ray_cast->verWallContent;
		rays[stripid].wasHitVertical = 1;
	}
	else
	{
		rays[stripid].distance = ray_cast->horHitDistance;
		rays[stripid].wallHitX = ray_cast->horWallHitX;
		rays[stripid].wallHitY = ray_cast->horWallHitY;
		rays[stripid].wallHitContent = ray_cast->horWallContent;
		rays[stripid].wasHitVertical = 0;
	}
	return (0);
}

int	assign_ray_properties(t_game *game, float rayAngle, int stripid)
{
	t_ray_cast	*ray_cast;
	t_ray		*rays;

	ray_cast = &game->ray_casts[stripid];
	rays = game->rays;
	rays[stripid].rayAngle = rayAngle;
	rays[stripid].isRayFacingDown = ray_cast->isRayFacingDown;
	rays[stripid].isRayFacingUp = ray_cast->isRayFacingUp;
	rays[stripid].isRayFacingLeft = ray_cast->isRayFacingLeft;
	rays[stripid].isRayFacingRight = ray_cast->isRayFacingRight;
	return (0);
}
