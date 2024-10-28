/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:22:07 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/28 10:57:00 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
