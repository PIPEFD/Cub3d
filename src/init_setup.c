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

#include "cub3d.h"

void	update(void *param)
{
	t_game			*game;
	unsigned int	timenow;

	game = (t_game *)param;
	timenow = mlx_get_time() * 1000;
	if (timenow - game->tickslastframe > 1000 / FRAMES)
	{
		move_player(game, &game->player);
		cast_all_rays(game);
		ft_memset(game->img->pixels, 0, game->img->width * game->img->height
			* sizeof(unsigned int));
		render_3d_projection(game);
		render_minimap(game);
		game->tickslastframe = timenow;
	}
}

int	init_data_all(t_game *game)
{
	init_data_player(game);
	init_data_rays(game);
	if (init_data_figures(game) != 0)
		return (-1);
	return (0);
}

int	setup(t_game *game)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", true);
	if (!game->mlx)
		return ((void)printf("Error initializing MLX.\n"), 0);
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (printf("Error creating image.\n"), -1);
	if (init_data_all(game) != 0)
		return (-1);
	return (0);
}
