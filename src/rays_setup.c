/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/14 00:38:55 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * Realiza el raycasting para un rayo específico.
 * @param game Puntero al juego.
 * @param rayAngle Ángulo del rayo.
 * @param stripid Índice del rayo.
 */
void	cast_ray(t_game *game, float rayAngle, int stripid)
{
	t_player	*player;
	t_ray_cast	*ray_cast;

	// Paso 1: Inicializar el rayo
	initialize_ray(game, &rayAngle, stripid);
	player = &game->player;
	ray_cast = &game->ray_casts[stripid];
	// Paso 2: Encontrar la intersección horizontal
	find_horizontal_hit(game, ray_cast, player, rayAngle);
	// Paso 3: Encontrar la intersección vertical
	find_vertical_hit(game, ray_cast, player, rayAngle);
	// Paso 4: Calcular distancias y determinar el impacto más cercano
	calculate_hit_distances(game, ray_cast, stripid);
	// Paso 5: Asignar propiedades al rayo
	assign_ray_properties(game, rayAngle, stripid);
}

/**
 * Realiza el raycasting para todos los rayos.
 * @param game Puntero al juego.
 */
void	cast_all_rays(t_game *game)
{
	float	rayAngle;

	rayAngle = game->player.rotationAngle - (FOV / 2);
	for (int stripid = 0; stripid < NUM_RAYS; stripid++)
	{
		cast_ray(game, rayAngle, stripid);
		rayAngle += FOV / NUM_RAYS;
	}
}
