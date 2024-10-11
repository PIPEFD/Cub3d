/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.com>  +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/09/25 21:49:01 by dbonilla          #+#    #+#             */
/*   Updated: 2024/09/25 21:49:01 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	destroy_window(t_game *game)
{
	int	i;

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
	if (game->map)
	{
		i = 0;
		while (i++ < MAP_NUM_ROWS)
		{
			free(game->map[i]);
		}
		free(game->map);
		game->map = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	 const char* direction_input = NULL;

    // Verificar si se proporcionó input de dirección
    if (argc > 1) {
        direction_input = argv[1];
	}
   	if (setup(&game, direction_input) != 0)
		return (-1);
	mlx_loop(game.mlx);
	destroy_window(&game);
	return (0);
}
