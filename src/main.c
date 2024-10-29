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

/*
git clone https://github.com/codam-coding-college/MLX42.git
cd MLX42
cmake -B build # build here refers to the outputfolder.
cmake --build build -j4 # or do make -C build -j4
*/

int	get_sprites(t_game *data)
{
	if (!data->no->file || !data->so->file || !data->we->file
		|| !data->ea->file)
		return (0);
	if (!load_sprite(data->no, -1, -1))
		return (0);
	if (!load_sprite(data->so, -1, -1))
		return (0);
	if (!load_sprite(data->we, -1, -1))
		return (0);
	if (!load_sprite(data->ea, -1, -1))
		return (0);
	return (1);
}

void	free_texture(t_texture **texture)
{
	if (*texture)
	{
		if ((*texture)->file)
		{
			free((*texture)->file);
			(*texture)->file = NULL;
		}
		free(*texture);
		*texture = NULL;
	}
}

void	mouse_hook(double xpos, double ypos, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ypos = (xpos > WINDOW_WIDTH / 2) - (xpos < WINDOW_WIDTH / 2);
	game->player.turndirection = ypos;
	if (xpos > WINDOW_WIDTH / 3 && xpos < WINDOW_WIDTH * 2 / 3)
		game->player.turndirection = 0;
}

void	freedom(t_game	*game)
{
	split_free(game->map);
	free_sprite(game->no);
	free_sprite(game->so);
	free_sprite(game->we);
	free_sprite(game->ea);
	destroy_window2(game);
	destroy_window4(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || !parsing(&game, argv[1]))
	{
		return (printf("Error parsing file.\n"), freedom(&game), -1);
	}
	game.img = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game.img)
		return (printf("Error creating image.\n"), -1);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_key_hook(game.mlx, &key_hook, &game);
	mlx_cursor_hook(game.mlx, &mouse_hook, &game);
	mlx_loop_hook(game.mlx, &update, &game);
	mlx_loop(game.mlx);
	destroy_window(&game);
	return (0);
}
