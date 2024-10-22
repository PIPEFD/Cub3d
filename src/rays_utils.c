/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/21 14:46:33 by kabasolo         ###   ########.fr       */
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
int	calculate_hit_distances(t_game *game, t_ray_cast *ray_cast, int stripid)
{
	t_player	*player;
	t_ray		*rays;

	player = &game->player;
	rays = game->rays;
	ray_cast->horHitDistance = (ray_cast->foundHorzWallhit) ? distance_between_points(player->x,
			player->y, ray_cast->horWallHitX, ray_cast->horWallHitY) : FLT_MAX;
	ray_cast->verHitDistance = (ray_cast->foundVerWallhit) ? distance_between_points(player->x,
			player->y, ray_cast->verWallHitX, ray_cast->verWallHitY) : FLT_MAX;
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
	/*
	printf("// --- // --- // --- // --- // --- //\n");
	printf("Rayos calculados\n");
	printf("// --- // --- // --- // --- // --- //\n");
	printf("RayAngle: [%f] \n number_of_ray -->> [%d]\n", rays[stripid].rayAngle, stripid);
	printf("Distance: [%f] \n number_of_ray -->> [%d]\n ", rays[stripid].distance, stripid);
	printf("WallHitX: [%f] \n number_of_ray -->> [%d]\n", rays[stripid].wallHitX, stripid);
	printf("WallHitY: [%f] \n number_of_ray -->> [%d]\n", rays[stripid].wallHitY, stripid);
	printf("WallHitContent: [%d] \n number_of_ray -->> [%d]\n", rays[stripid].wallHitContent, stripid);
	printf("WasHitVertical: [%d] \n number_of_ray -->> [%d]\n", rays[stripid].wasHitVertical, stripid);
	printf("IsRayFacingUp: [%d] \n number_of_ray -->> [%d]\n", rays[stripid].isRayFacingUp, stripid);
	printf("IsRayFacingDown: [%d] \n number_of_ray -->> [%d]\n", rays[stripid].isRayFacingDown, stripid);
	printf("IsRayFacingLeft: [%d] \n number_of_ray -->> [%d]\n", rays[stripid].isRayFacingLeft, stripid);
	printf("IsRayFacingRight: [%d] \n number_of_ray -->> [%d]\n", rays[stripid].isRayFacingRight, stripid);
	printf("// --- // --- // --- // --- // --- //\n");
	*/
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
