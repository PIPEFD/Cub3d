/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:26:49 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/29 17:06:24 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data_bresenham(t_bresenham_vars *vars, t_line_params *params)
{
	vars->x0 = params->x0;
	vars->y0 = params->y0;
	vars->x1 = params->x1;
	vars->y1 = params->y1;
	vars->dx = ft_abs(vars->x1 - vars->x0);
	vars->dy = -ft_abs(vars->y1 - vars->y0);
	vars->sx = (vars->x0 < vars->x1) - (vars->x0 >= vars->x1);
	vars->sy = (vars->y0 < vars->y1) - (vars->y0 >= vars->y1);
	vars->err = vars->dx + vars->dy;
}

int	init_data_figures(t_game *game)
{
	game->draw_figures.rect_params = malloc(sizeof(t_rectangle_params));
	if (!game->draw_figures.rect_params)
		return (printf("Error al asignar memoria para line_params\n"), -1);
	ft_memset(game->draw_figures.rect_params, 0, sizeof(t_rectangle_params));
	game->draw_figures.line_params = malloc(sizeof(t_line_params));
	if (!game->draw_figures.line_params)
		return (printf("Error al asignar memoria para line_params\n"), -1);
	ft_memset(game->draw_figures.line_params, 0, sizeof(t_line_params));
	game->draw_figures.line_draw = malloc(sizeof(t_line_params));
	if (!game->draw_figures.line_draw)
		return (printf("Error al asignar memoria para line_params\n"), -1);
	ft_memset(game->draw_figures.line_draw, 0, sizeof(t_line_params));
	return (0);
}

void	init_data_rays(t_game *game)
{
	ft_memset(&game->rays, 0, sizeof(t_ray));
	ft_memset(&game->ray_casts, 0, sizeof(t_ray_cast));
}

void	init_data_player(t_game *game)
{
	game->player.turndirection = 0;
	game->player.strafedirection = 0;
	game->player.walkdirection = 0;
	game->player.rotationangle = PI / 2;
	game->player.walkspeed = SPEED;
	game->player.turnspeed = TURN_SPEED * (PI / 180);
	game->tickslastframe = 0;
	game->player.fov = (60 * PI / 180);
	set_player_direction(&game->player);
}

void	init_data(t_game *data)
{
	data->player.dir = 0;
	data->no = (t_texture *)malloc(sizeof(t_texture));
	data->no->img = NULL;
	data->so = (t_texture *)malloc(sizeof(t_texture));
	data->so->img = NULL;
	data->ea = (t_texture *)malloc(sizeof(t_texture));
	data->ea->img = NULL;
	data->we = (t_texture *)malloc(sizeof(t_texture));
	data->we->img = NULL;
	data->ceiling = 0;
	data->floor = 0;
	data->map = NULL;
}
