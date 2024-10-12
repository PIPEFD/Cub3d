/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/12 01:20:51 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	initHorizontalRayVars(t_ray_cast *ray_cast)
{
	// Inicialización de variables relacionadas con el impacto del rayo
	ray_cast->foundHorzWallhit = 0;
	ray_cast->horWallHitX = 0;
	ray_cast->horWallHitY = 0;
	ray_cast->horWallContent = 0;
}

void	calculateHorizontalIntercepts(t_game *game, t_ray_cast *ray_cast,
		float rayAngle)
{
	t_player	*player;

	player = &game->player;
	// Cálculo de la intersección inicial en Y
	ray_cast->yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
	if (ray_cast->isRayFacingDown)
	{
		ray_cast->yintercept += TILE_SIZE;
	}
	// Cálculo de la intersección inicial en X
	ray_cast->xintercept = player->x + (ray_cast->yintercept - player->y)
		/ tan(rayAngle);
}

void	calculateHorizontalSteps(t_ray_cast *ray_cast, float rayAngle)
{
	// Determinación de los pasos en Y
	if (ray_cast->isRayFacingUp)
	{
		ray_cast->ystep = -TILE_SIZE;
	}
	else
	{
		ray_cast->ystep = TILE_SIZE;
	}
	// Determinación de los pasos en X
	ray_cast->xstep = TILE_SIZE / tan(rayAngle);
	// Ajustes según la dirección del rayo
	if (ray_cast->isRayFacingLeft && ray_cast->xstep > 0)
	{
		ray_cast->xstep *= -1;
	}
	if (ray_cast->isRayFacingRight && ray_cast->xstep < 0)
	{
		ray_cast->xstep *= -1;
	}
	// Inicialización de los puntos de intersección
	ray_cast->nextHorzTouchX = ray_cast->xintercept;
	ray_cast->nextHorzTouchY = ray_cast->yintercept;
}

int	checkHorizontalWallHit(t_game *game, t_ray_cast *ray_cast)
{
	float	xToCheck;
	float	yToCheck;

	xToCheck = ray_cast->nextHorzTouchX;
	yToCheck = ray_cast->nextHorzTouchY;
	// Ajuste para verificar si el rayo se enfrenta hacia arriba
	if (ray_cast->isRayFacingUp)
	{
		yToCheck -= 1;
	}
	// Verificar si el rayo ha impactado una pared
	if (mapHasWallAt(game, xToCheck, yToCheck))
	{
		ray_cast->horWallHitX = ray_cast->nextHorzTouchX;
		ray_cast->horWallHitY = ray_cast->nextHorzTouchY;
		ray_cast->horWallContent = game->map[(int)floor(yToCheck
				/ TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
		ray_cast->foundHorzWallhit = 1;
		return (1); // Pared encontrada
	}
	return (0); // No se encontró pared
}

void	updateHorizontalTouchPoints(t_ray_cast *ray_cast)
{
	// Actualización de los puntos de toque horizontales para la siguiente iteración
	ray_cast->nextHorzTouchX += ray_cast->xstep;
	ray_cast->nextHorzTouchY += ray_cast->ystep;
}

void	castHorizontalRay(t_game *game, t_ray_cast *ray_cast, float rayAngle)
{
	// Inicialización de variables
	initHorizontalRayVars(ray_cast);
	// Calcular intersecciones iniciales
	calculateHorizontalIntercepts(game, ray_cast, rayAngle);
	// Calcular los pasos que tomará el rayo
	calculateHorizontalSteps(ray_cast, rayAngle);
	// Bucle para encontrar la intersección horizontal
	while (ray_cast->nextHorzTouchX >= 0
		&& ray_cast->nextHorzTouchX <= WINDOW_WIDTH
		&& ray_cast->nextHorzTouchY >= 0
		&& ray_cast->nextHorzTouchY <= WINDOW_HEIGHT)
	{
		// Verificar si el rayo impacta una pared
		if (checkHorizontalWallHit(game, ray_cast))
		{
			break ; // Si encontramos una pared, salimos del bucle
		}
		// Si no hay pared, actualizar los puntos de toque horizontales
		updateHorizontalTouchPoints(ray_cast);
	}
}
