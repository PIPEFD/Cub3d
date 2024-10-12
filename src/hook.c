/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:22:07 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/12 01:17:28 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void handle_walk_input(mlx_key_data_t keydata, t_game *game)
{
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
}

void handle_strafe_input(mlx_key_data_t keydata, t_game *game)
{
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
}

void handle_turn_input(mlx_key_data_t keydata, t_game *game)
{
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

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        mlx_close_window(game->mlx);
    }

    // Manejar el movimiento hacia adelante y atrás
    handle_walk_input(keydata, game);

    // Manejar el movimiento lateral (strafe)
    handle_strafe_input(keydata, game);

    // Manejar la rotación del jugador
    handle_turn_input(keydata, game);
}

