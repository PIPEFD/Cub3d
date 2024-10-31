/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:22:07 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/31 16:39:17 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	player_wall(t_game *game, float x, float y)
{
	int		map_grid_index_x;
	int		map_grid_index_y;
	int		offset_x;
	int		offset_y;
	char	tile;

	offset_y = -2;
	while (++offset_y <= 1)
	{
		offset_x = -2;
		while (++offset_x <= 1)
		{
			map_grid_index_x = ((int)(x + offset_x * 0.1) / TILE_SIZE);
			map_grid_index_y = ((int)(y + offset_y * 0.1) / TILE_SIZE);
			if (map_grid_index_y >= 0 && map_grid_index_x >= 0 && \
				map_grid_index_y < split_len(game->map) && map_grid_index_x < \
				(int)ft_strlen(game->map[map_grid_index_y]))
			{
				tile = game->map[map_grid_index_y][map_grid_index_x];
				if (tile != '0')
					return (1);
			}
		}
	}
	return (0);
}

void	handle_walk_input(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_W)
	{
		if (keydata.action == MLX_PRESS)
			game->player.walkdirection = +1;
		else if (keydata.action == MLX_RELEASE)
			game->player.walkdirection = 0;
	}
	if (keydata.key == MLX_KEY_S)
	{
		if (keydata.action == MLX_PRESS)
			game->player.walkdirection = -1;
		else if (keydata.action == MLX_RELEASE)
			game->player.walkdirection = 0;
	}
}

void	handle_strafe_input(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_A)
	{
		if (keydata.action == MLX_PRESS)
			game->player.strafedirection = -1;
		else if (keydata.action == MLX_RELEASE)
			game->player.strafedirection = 0;
	}
	if (keydata.key == MLX_KEY_D)
	{
		if (keydata.action == MLX_PRESS)
			game->player.strafedirection = +1;
		else if (keydata.action == MLX_RELEASE)
			game->player.strafedirection = 0;
	}
}

void	handle_turn_input(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_RIGHT)
	{
		if (keydata.action == MLX_PRESS)
			game->player.turndirection = +1;
		else if (keydata.action == MLX_RELEASE)
			game->player.turndirection = 0;
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		if (keydata.action == MLX_PRESS)
			game->player.turndirection = -1;
		else if (keydata.action == MLX_RELEASE)
			game->player.turndirection = 0;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	handle_walk_input(keydata, game);
	handle_strafe_input(keydata, game);
	handle_turn_input(keydata, game);
}
