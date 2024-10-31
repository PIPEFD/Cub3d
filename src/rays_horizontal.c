/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/31 16:39:17 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initialize_horizontal_ray(t_ray_cast *ray_cast, t_player *player,
		float rayAngle)
{
	ray_cast->foundhorzwallhit = 0;
	ray_cast->horwallhitx = 0;
	ray_cast->horwallhity = 0;
	ray_cast->horwallcontent = 0;
	ray_cast->yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
	if (ray_cast->israyfacingdown)
		ray_cast->yintercept += TILE_SIZE;
	ray_cast->xintercept = player->x + (ray_cast->yintercept - player->y)
		/ tan(rayAngle);
	ray_cast->ystep = TILE_SIZE;
	if (ray_cast->israyfacingup)
		ray_cast->ystep *= -1;
	ray_cast->xstep = TILE_SIZE / tan(rayAngle);
	if (ray_cast->israyfacingleft && ray_cast->xstep > 0)
		ray_cast->xstep *= -1;
	else if (ray_cast->israyfacingright && ray_cast->xstep < 0)
		ray_cast->xstep *= -1;
	ray_cast->nexthorztouchx = ray_cast->xintercept;
	ray_cast->nexthorztouchy = ray_cast->yintercept;
}

void	find_horizontal_hit(t_game *game, t_ray_cast *ray_cast,
		t_player *player, float rayAngle)
{
	float	xtocheck;
	float	ytocheck;

	initialize_horizontal_ray(ray_cast, player, rayAngle);
	while (ray_cast->nexthorztouchx >= 0
		&& ray_cast->nexthorztouchx <= game->width
		&& ray_cast->nexthorztouchy >= 0
		&& ray_cast->nexthorztouchy <= game->heigth)
	{
		xtocheck = ray_cast->nexthorztouchx;
		ytocheck = ray_cast->nexthorztouchy;
		if (ray_cast->israyfacingup)
			ytocheck -= 1;
		if (map_has_wall_at(game, xtocheck, ytocheck))
		{
			ray_cast->horwallhitx = ray_cast->nexthorztouchx;
			ray_cast->horwallhity = ray_cast->nexthorztouchy;
			ray_cast->foundhorzwallhit = 1;
			break ;
		}
		ray_cast->nexthorztouchx += ray_cast->xstep;
		ray_cast->nexthorztouchy += ray_cast->ystep;
	}
}
