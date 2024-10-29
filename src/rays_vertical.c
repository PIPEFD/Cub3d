/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/29 16:56:05 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_vertical_ray(t_ray_cast *ray_cast, t_player *player,
		float rayAngle)
{
	ray_cast->foundverwallhit = 0;
	ray_cast->verwallhitx = 0;
	ray_cast->verwallhity = 0;
	ray_cast->verwallcontent = 0;
	ray_cast->xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
	if (ray_cast->israyfacingright)
		ray_cast->xintercept += TILE_SIZE;
	ray_cast->yintercept = player->y + (ray_cast->xintercept - player->x)
		* tan(rayAngle);
	ray_cast->xstep = TILE_SIZE;
	if (ray_cast->israyfacingleft)
		ray_cast->xstep *= -1;
	ray_cast->ystep = TILE_SIZE * tan(rayAngle);
	if (ray_cast->israyfacingup && ray_cast->ystep > 0)
		ray_cast->ystep *= -1;
	else if (ray_cast->israyfacingdown && ray_cast->ystep < 0)
		ray_cast->ystep *= -1;
	ray_cast->nextvertouchx = ray_cast->xintercept;
	ray_cast->nextvertouchy = ray_cast->yintercept;
}

void	find_vertical_hit(t_game *game, t_ray_cast *ray_cast, t_player *player,
		float rayAngle)
{
	float	xtocheck;
	float	ytocheck;

	initialize_vertical_ray(ray_cast, player, rayAngle);
	while (ray_cast->nextvertouchx >= 0
		&& ray_cast->nextvertouchx <= game->width
		&& ray_cast->nextvertouchy >= 0
		&& ray_cast->nextvertouchy <= game->heigth)
	{
		xtocheck = ray_cast->nextvertouchx;
		ytocheck = ray_cast->nextvertouchy;
		if (ray_cast->israyfacingleft)
			xtocheck -= 1;
		ytocheck = ray_cast->nextvertouchy;
		if (map_has_wall_at(game, xtocheck, ytocheck))
		{
			ray_cast->verwallhitx = ray_cast->nextvertouchx;
			ray_cast->verwallhity = ray_cast->nextvertouchy;
			ray_cast->foundverwallhit = 1;
			break ;
		}
		ray_cast->nextvertouchx += ray_cast->xstep;
		ray_cast->nextvertouchy += ray_cast->ystep;
	}
}
