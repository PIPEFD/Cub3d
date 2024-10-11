/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:49:01 by dbonilla          #+#    #+#             */
/*   Updated: 2024/09/25 21:49:01 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void destroyWindow(t_game* game)
{
    if (game->img)
    {
        mlx_delete_image(game->mlx, game->img);
        game->img = NULL;
    }
    if (game->mlx)
    {
        mlx_terminate(game->mlx);
        game->mlx = NULL;
    }
    // Liberar memoria del mapa
    if (game->map)
    {
        for (int i = 0; i < MAP_NUM_ROWS; i++)
        {
            free(game->map[i]);
        }
        free(game->map);
        game->map = NULL;
    }
}


int main()
{
    t_game game;
    
    setup(&game);

    mlx_loop(game.mlx);

    destroyWindow(&game);

    return 0;
}