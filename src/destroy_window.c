/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:56:20 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/29 16:13:17 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_sprite(t_texture *text)
{
	int	y;

	y = 0;
	if (text->img)
	{
		while (y < text->height)
		{
			if (text->img[y])
				free(text->img[y]);
			y++;
		}
		free(text->img);
		text->img = NULL;
	}
}

void	destroy_window3(t_game *game)
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

void	destroy_window4(t_game *game)
{
	if (game->no)
	{
		free(game->no->file);
		free(game->no->img);
		free(game->no);
		game->no = NULL;
	}
	if (game->so)
	{
		free(game->so->file);
		free(game->so->img);
		free(game->so);
		game->so = NULL;
	}
}

void	destroy_window2(t_game *game)
{
	if (game->we)
	{
		free(game->we->file);
		free(game->we->img);
		free(game->we);
		game->we = NULL;
	}
	if (game->ea)
	{
		free(game->ea->file);
		free(game->ea->img);
		free(game->ea);
		game->ea = NULL;
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
	split_free(game->map);
	free_sprite(game->no);
	free_sprite(game->so);
	free_sprite(game->we);
	free_sprite(game->ea);
	destroy_window2(game);
	destroy_window3(game);
	destroy_window4(game);
}
