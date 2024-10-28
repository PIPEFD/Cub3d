/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/28 11:11:58 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	rayangle = game->player.rotationangle - (FOV / 2);
	while (stripid < NUM_RAYS)
	{
		if (cast_ray_setup(game, rayangle, stripid) != 0)
			break ;
		rayangle += FOV / NUM_RAYS;
		stripid++;
	}
}
