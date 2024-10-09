/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:22:07 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/09 16:05:50 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"



void key_hook(mlx_key_data_t keydata, t_player *player, mlx_t *mlx)
{
    // (void)param; // Unused parameter
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        mlx_close_window(mlx);
    }
    if (keydata.key == MLX_KEY_UP)
    {
        if (keydata.action == MLX_PRESS)
            player->walkDirection = +1;
        else if (keydata.action == MLX_RELEASE)
            player->walkDirection = 0;
    }
    if (keydata.key == MLX_KEY_DOWN)
    {
        if (keydata.action == MLX_PRESS)
            player->walkDirection = -1;
        else if (keydata.action == MLX_RELEASE)
            player->walkDirection = 0;
    }
    if (keydata.key == MLX_KEY_RIGHT)
    {
        if (keydata.action == MLX_PRESS)
            player->turnDirection = +1;
        else if (keydata.action == MLX_RELEASE)
            player->turnDirection = 0;
    }
    if (keydata.key == MLX_KEY_LEFT)
    {
        if (keydata.action == MLX_PRESS)
            player->turnDirection = -1;
        else if (keydata.action == MLX_RELEASE)
            player->turnDirection = 0;
    }
}