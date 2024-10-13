/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:26:49 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/13 18:13:48 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	data_init_rays(t_game *game)
{
	ft_memset(game->rays, 0, sizeof(t_ray) * NUM_RAYS);
	ft_memset(game->ray_casts, 0, sizeof(t_ray_cast) * NUM_RAYS);
	return (0);
}

int	init_data_player(t_game *game, const char *direction_input)
{
	game->player.x = WINDOW_WIDTH / 2;
	game->player.y = WINDOW_HEIGHT / 2;
	game->player.width = 1;
	game->player.height = 1;
	game->player.turnDirection = 0;
	game->player.strafeDirection = 0;
	game->player.walkDirection = 0;
	game->player.rotationAngle = PI / 2;
	game->player.walkSpeed = 150;
	game->player.turnSpeed = 80 * (PI / 180);
	game->ticksLastFrame = 0;
	if (direction_input != NULL)
	{
		set_player_direction(&game->player, direction_input);
	}
	else
	{
		game->player.rotationAngle = PI / 2;
	}
	return (0);
}

int	init_data_map(t_game *game)
{
	const char	*mapdata[MAP_NUM_ROWS] = {"111111111111111", "100000000000101",
		"100100000000101", "101110000010101", "100000000010101",
		"100000001111101", "100000000000001", "100000000000001",
		"111111000111101", "100000000000001", "111111111111111"};
	int			i;

	game->map = malloc(sizeof(char *) * MAP_NUM_ROWS);
	if (!game->map)
		return ('\0');
	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		game->map[i] = ft_strdup(mapdata[i]);
		if (!game->map[i])
		{
			printf("Error duplicating map row.\n");
			return (-1);
		}
		i++;
		printf("[%d]", i);
	}
	return (0);
}
