/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/12 01:06:55 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void initVerticalRayIntercepts(t_game *game, t_ray_cast *ray_cast, float rayAngle)
{
    t_player *player = &game->player;

    // Inicialización de las variables de colisión vertical
    ray_cast->foundVerWallhit = 0;
    ray_cast->verWallHitX = 0;
    ray_cast->verWallHitY = 0;
    ray_cast->verWallContent = 0;

    // Cálculo de la intersección inicial en X
    ray_cast->xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    if (ray_cast->isRayFacingRight) {
        ray_cast->xintercept += TILE_SIZE;
    }

    // Cálculo de la intersección inicial en Y usando la intersección X
    ray_cast->yintercept = player->y + (ray_cast->xintercept - player->x) * tan(rayAngle);
}

void initVerticalRaySteps(t_ray_cast *ray_cast, float rayAngle) {
    // Determinación de los pasos en X dependiendo de la dirección del rayo
    if (ray_cast->isRayFacingLeft) {
        ray_cast->xstep = -TILE_SIZE;
    } else {
        ray_cast->xstep = TILE_SIZE;
    }

    // Determinación de los pasos en Y
    ray_cast->ystep = TILE_SIZE * tan(rayAngle);

    // Ajuste de los pasos en Y dependiendo de la dirección del rayo
    if (ray_cast->isRayFacingUp && ray_cast->ystep > 0) {
        ray_cast->ystep *= -1;
    } else if (ray_cast->isRayFacingDown && ray_cast->ystep < 0) {
        ray_cast->ystep *= -1;
    }

    // Configuración de los siguientes puntos de intersección vertical
    ray_cast->nextVerTouchX = ray_cast->xintercept;
    ray_cast->nextVerTouchY = ray_cast->yintercept;
}


int	checkVerticalWallHit(t_game *game, t_ray_cast *ray_cast)
{
	float	xToCheck;
	float	yToCheck;

	xToCheck = ray_cast->nextVerTouchX;
	yToCheck = ray_cast->nextVerTouchY;
	if (ray_cast->isRayFacingLeft)
	{
		xToCheck -= 1;
	}
	// Verificación de colisión con una pared
	if (mapHasWallAt(game, xToCheck, yToCheck))
	{
		ray_cast->verWallHitX = ray_cast->nextVerTouchX;
		ray_cast->verWallHitY = ray_cast->nextVerTouchY;
		ray_cast->verWallContent = game->map[(int)floor(yToCheck
				/ TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
		ray_cast->foundVerWallhit = 1;
		return (1); // Pared encontrada
	}
	return (0); // No hay pared
}

void	moveToNextVerticalIntersection(t_ray_cast *ray_cast)
{
	// Movemos el rayo al siguiente punto de intersección vertical
	ray_cast->nextVerTouchX += ray_cast->xstep;
	ray_cast->nextVerTouchY += ray_cast->ystep;
}

void	castVerticalRay(t_game *game, t_ray_cast *ray_cast, float rayAngle)
{
	// Inicializar los valores del rayo vertical
	initVerticalRay(game, ray_cast, rayAngle);
	// Bucle para encontrar la intersección vertical
	while (ray_cast->nextVerTouchX >= 0
		&& ray_cast->nextVerTouchX <= WINDOW_WIDTH
		&& ray_cast->nextVerTouchY >= 0
		&& ray_cast->nextVerTouchY <= WINDOW_HEIGHT)
	{
		// Verificar si hay una pared en la intersección actual
		if (checkVerticalWallHit(game, ray_cast))
		{
			break ; // Si encontramos una pared, salimos del bucle
		}
		// Si no hay pared, movemos al siguiente punto de intersección
		moveToNextVerticalIntersection(ray_cast);
	}
}
