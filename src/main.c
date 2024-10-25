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

void	destroy_window(t_game *game)
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
	split_free(game->map);

	// if (game->rays)
	// {
	// 	free(game->rays);
	// 	game->rays = NULL;
	// }
	// if (game->ray_casts)
	// {
	// 	free(game->ray_casts);
	// 	game->ray_casts = NULL;
	// }
	if (game->draw_figures.rect_params)
	{
		free(game->draw_figures.rect_params);
		game->draw_figures.rect_params = NULL;
	}
	if (game->draw_figures.line_params)
	{
		free(game->draw_figures.line_params);
		game->draw_figures.line_params = NULL;
	}
	if (game->draw_figures.line_draw)
	{
		free(game->draw_figures.line_draw);
		game->draw_figures.line_draw = NULL;
	}
	
	
}
/*
void print_image(t_texture *text, mlx_image_t *img, int scale)
{
	int	y;
	int	x;
	int i;
	int	j;

	y = -1;
	while (++y < text->height)
	{
		x = -1;
		while (++x < text->width2)
		{
			j = -1;
			while (++j < scale)
			{
				i = -1;
				while (++i < scale)
					mlx_put_pixel(img, i + x * scale, j + y * scale, text->img[y][x]);
			}
		}
	}
}
*/

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2 || !parsing(&game, argv[1]))
		return (1);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	//print_image(game.no, game.img, 50);
	mlx_key_hook(game.mlx, &key_hook, &game);
	mlx_loop_hook(game.mlx, &update, &game);
	mlx_loop(game.mlx);
	destroy_window(&game);
	return (0);
}
