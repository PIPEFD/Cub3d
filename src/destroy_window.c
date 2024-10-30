/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:56:20 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/30 14:45:31 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_window2(t_game *game)
{
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
	//split_free(game->map);
	//free_sprite(game->no);
	//free_sprite(game->so);
	//free_sprite(game->we);
	//free_sprite(game->ea);
	destroy_window2(game);
}
