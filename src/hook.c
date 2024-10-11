/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:22:07 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/11 13:43:57 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(game->mlx);
	}
	// Movimiento hacia adelante y atrás con W y S
	if (keydata.key == MLX_KEY_W)
	{
		if (keydata.action == MLX_PRESS)
			game->player.walkDirection = +1;
		else if (keydata.action == MLX_RELEASE)
			game->player.walkDirection = 0;
	}
	if (keydata.key == MLX_KEY_S)
	{
		if (keydata.action == MLX_PRESS)
			game->player.walkDirection = -1;
		else if (keydata.action == MLX_RELEASE)
			game->player.walkDirection = 0;
	}
	// Movimiento lateral (strafing) con A y D
	if (keydata.key == MLX_KEY_A)
	{
		if (keydata.action == MLX_PRESS)
			game->player.strafeDirection = -1;
		else if (keydata.action == MLX_RELEASE)
			game->player.strafeDirection = 0;
	}
	if (keydata.key == MLX_KEY_D)
	{
		if (keydata.action == MLX_PRESS)
			game->player.strafeDirection = +1;
		else if (keydata.action == MLX_RELEASE)
			game->player.strafeDirection = 0;
	}
	// Rotación con teclas de flecha izquierda y derecha
	if (keydata.key == MLX_KEY_RIGHT)
	{
		if (keydata.action == MLX_PRESS)
			game->player.turnDirection = +1;
		else if (keydata.action == MLX_RELEASE)
			game->player.turnDirection = 0;
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		if (keydata.action == MLX_PRESS)
			game->player.turnDirection = -1;
		else if (keydata.action == MLX_RELEASE)
			game->player.turnDirection = 0;
	}
}
