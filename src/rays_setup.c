/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/17 12:22:30 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cast_ray_setup(t_game *game, float rayAngle, int stripid)
{
	t_player	*player;
	t_ray_cast	*ray_cast;

	// Paso 1: Inicializar el rayo
	if (initialize_ray(game, &rayAngle, stripid) != 0)
		return (-1);
	player = &game->player;
	ray_cast = &game->ray_casts[stripid];
	// Paso 2: Encontrar la intersección horizontal
	if (find_horizontal_hit(game, ray_cast, player, rayAngle) != 0)
		return (-1);
	// Paso 3: Encontrar la intersección vertical
	if (find_vertical_hit(game, ray_cast, player, rayAngle) != 0)
		return (-1);
	// Paso 4: Calcular distancias y determinar el impacto más cercano
	if (calculate_hit_distances(game, ray_cast, stripid) != 0)
		return (-1);
	// Paso 5: Asignar propiedades al rayo
	if (assign_ray_properties(game, rayAngle, stripid) != 0)
		return (-1);
	return (0);
}
void	cast_all_rays(t_game *game)
{
	float	rayAngle;
	int stripid;

	stripid = 0;
	rayAngle = game->player.rotationAngle - (FOV / 2);
	while (stripid < NUM_RAYS)
	{
		if (cast_ray_setup(game, rayAngle, stripid) != 0)
			break ;
		rayAngle += FOV / NUM_RAYS;
		stripid++;
	}
}
