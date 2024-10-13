/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/14 00:25:37 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


/**
 * Encuentra la intersección horizontal más cercana del rayo con una pared.
 * @param game Puntero al juego.
 * @param ray_cast Puntero a la estructura de raycasting.
 * @param player Puntero al jugador.
 * @param rayAngle Ángulo del rayo.
 */
void	find_horizontal_hit(t_game *game, t_ray_cast *ray_cast,
		t_player *player, float rayAngle)
{
	float	xToCheck;
	float	yToCheck;

	ray_cast->foundHorzWallhit = 0;
	ray_cast->horWallHitX = 0;
	ray_cast->horWallHitY = 0;
	ray_cast->horWallContent = 0;
	ray_cast->yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
	ray_cast->yintercept += ray_cast->isRayFacingDown ? TILE_SIZE : 0;
	ray_cast->xintercept = player->x + (ray_cast->yintercept - player->y)
		/ tan(rayAngle);
	ray_cast->ystep = TILE_SIZE;
	ray_cast->ystep *= ray_cast->isRayFacingUp ? -1 : 1;
	ray_cast->xstep = TILE_SIZE / tan(rayAngle);
	ray_cast->xstep *= (ray_cast->isRayFacingLeft && ray_cast->xstep > 0) ?
		-1 : 1;
	ray_cast->xstep *= (ray_cast->isRayFacingRight && ray_cast->xstep < 0) ?
		-1 : 1;
	ray_cast->nextHorzTouchX = ray_cast->xintercept;
	ray_cast->nextHorzTouchY = ray_cast->yintercept;
	while (ray_cast->nextHorzTouchX >= 0
		&& ray_cast->nextHorzTouchX <= WINDOW_WIDTH
		&& ray_cast->nextHorzTouchY >= 0
		&& ray_cast->nextHorzTouchY <= WINDOW_HEIGHT)
	{
		xToCheck = ray_cast->nextHorzTouchX;
		yToCheck = ray_cast->nextHorzTouchY + (ray_cast->isRayFacingUp ?
				-1 : 0);
		if (map_has_wall_at(game, xToCheck, yToCheck))
		{
			ray_cast->horWallHitX = ray_cast->nextHorzTouchX;
			ray_cast->horWallHitY = ray_cast->nextHorzTouchY;
			ray_cast->horWallContent = game->map[(int)floor(yToCheck
					/ TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			ray_cast->foundHorzWallhit = 1;
			break ;
		}
		else
		{
			ray_cast->nextHorzTouchX += ray_cast->xstep;
			ray_cast->nextHorzTouchY += ray_cast->ystep;
		}
	}
}
