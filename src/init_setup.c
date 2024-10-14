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

void	update(void *param)
{
	t_game			*game;
	unsigned int	timenow;
	float			deltatime;

	game = (t_game *)param;
	timenow = mlx_get_time() * 1000;
	deltatime = (timenow - game->ticksLastFrame) / 1000.0f;
	game->ticksLastFrame = timenow;
	move_player(game, deltatime);
		
	cast_all_rays(game);
	ft_memset(game->img->pixels, 0, game->img->width * game->img->height
		* sizeof(unsigned int));
	render_3d_projection(game);
	render_map(game);
	render_rays(game);
	render_player(game);
}

int	init_data_all(t_game *game, const char *direction_input)
{
	if (init_data_player(game, direction_input) != 0)
		return (-1);
	if (init_data_map(game) != 0)
		return (-1);
	if (init_data_rays(game) != 0)
		return (-1);
	if (init_data_figures(game) != 0)
		return (-1);
	printf("\nInitialized data correctly\n");
	return (0);
}

int	setup(t_game *game, const char *direction_input)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", true);
	if (!game->mlx)
	{
		printf("Error initializing MLX.\n");
		return (-1);
	}
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
	{
		printf("Error creating image.\n");
		return (-1);
	}
	if (init_data_all(game, direction_input) != 0)
		return (-1);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_key_hook(game->mlx, &key_hook, game);
	mlx_loop_hook(game->mlx, &update, game);
	return (0);
}
