/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/31 16:39:17 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	initialize_ray(t_game *game, float *rayAngle, int stripid)
{
	t_ray_cast	*ray_cast;

	*rayAngle = normalize_angle(*rayAngle);
	ray_cast = &game->ray_casts[stripid];
	ray_cast->israyfacingdown = (*rayAngle > 0 && *rayAngle < PI);
	ray_cast->israyfacingup = !ray_cast->israyfacingdown;
	ray_cast->israyfacingright = (*rayAngle < 0.5 * PI || *rayAngle > 1.5 * PI);
	ray_cast->israyfacingleft = !ray_cast->israyfacingright;
	return (0);
}

void	set_hit_distances(t_game *game, t_ray_cast *ray_cast)
{
	t_player	*player;

	player = &game->player;
	if (ray_cast->foundhorzwallhit)
		ray_cast->horhitdistance = distance_between_points(player->x, player->y,
				ray_cast->horwallhitx, ray_cast->horwallhity);
	else
		ray_cast->horhitdistance = FLOAT_MAX;
	if (ray_cast->foundverwallhit)
		ray_cast->verhitdistance = distance_between_points(player->x, player->y,
				ray_cast->verwallhitx, ray_cast->verwallhity);
	else
		ray_cast->verhitdistance = FLOAT_MAX;
}

int	calculate_hit_distances(t_game *game, t_ray_cast *ray_cast, int stripid)
{
	t_ray	*rays;

	rays = game->rays;
	set_hit_distances(game, ray_cast);
	if (ray_cast->verhitdistance < ray_cast->horhitdistance)
	{
		rays[stripid].distance = ray_cast->verhitdistance;
		rays[stripid].wallhitx = ray_cast->verwallhitx;
		rays[stripid].wallhity = ray_cast->verwallhity;
		rays[stripid].wallhitcontent = ray_cast->verwallcontent;
		rays[stripid].washitvertical = 1;
	}
	else
	{
		rays[stripid].distance = ray_cast->horhitdistance;
		rays[stripid].wallhitx = ray_cast->horwallhitx;
		rays[stripid].wallhity = ray_cast->horwallhity;
		rays[stripid].wallhitcontent = ray_cast->horwallcontent;
		rays[stripid].washitvertical = 0;
	}
	return (0);
}

int	assign_ray_properties(t_game *game, float rayAngle, int stripid)
{
	t_ray_cast	*ray_cast;
	t_ray		*rays;

	ray_cast = &game->ray_casts[stripid];
	rays = game->rays;
	rays[stripid].rayangle = rayAngle;
	rays[stripid].israyfacingdown = ray_cast->israyfacingdown;
	rays[stripid].israyfacingup = ray_cast->israyfacingup;
	rays[stripid].israyfacingleft = ray_cast->israyfacingleft;
	rays[stripid].israyfacingright = ray_cast->israyfacingright;
	return (0);
}
