/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/31 16:39:17 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	cast_ray_setup(t_game *game, float rayAngle, int stripid)
{
	t_player	*player;
	t_ray_cast	*ray_cast;

	if (initialize_ray(game, &rayAngle, stripid) != 0)
		return (-1);
	player = &game->player;
	ray_cast = &game->ray_casts[stripid];
	find_horizontal_hit(game, ray_cast, player, rayAngle);
	find_vertical_hit(game, ray_cast, player, rayAngle);
	if (calculate_hit_distances(game, ray_cast, stripid) != 0)
		return (-1);
	if (assign_ray_properties(game, rayAngle, stripid) != 0)
		return (-1);
	return (0);
}

void	cast_all_rays(t_game *game)
{
	float	rayangle;
	int		stripid;

	stripid = 0;
	rayangle = game->player.rotationangle - (game->player.fov / 2);
	while (stripid < NUM_RAYS)
	{
		if (cast_ray_setup(game, rayangle, stripid) != 0)
			break ;
		rayangle += game->player.fov / NUM_RAYS;
		stripid++;
	}
}
