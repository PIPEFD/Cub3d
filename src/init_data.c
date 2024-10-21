/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:26:49 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/21 11:01:08 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_data_bresenham(t_bresenham_vars *vars, t_line_params *params)
{
	vars->x0 = params->x0;
	vars->y0 = params->y0;
	vars->x1 = params->x1;
	vars->y1 = params->y1;
	vars->dx = abs(vars->x1 - vars->x0);
	vars->dy = -abs(vars->y1 - vars->y0);
	vars->sx = (vars->x0 < vars->x1) - (vars->x0 >= vars->x1);  // Magia Koldiana
	vars->sy = (vars->y0 < vars->y1) - (vars->y0 >= vars->y1); // Magia Koldiana
	vars->err = vars->dx + vars->dy;
	return (0);
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
	memset(game->draw_figures.line_params, 0, sizeof(t_line_params));
	game->draw_figures.line_draw = malloc(sizeof(t_line_params));
	if (!game->draw_figures.line_draw)
		return (printf("Error al asignar memoria para line_params\n"), -1);
	memset(game->draw_figures.line_draw, 0, sizeof(t_line_params));
	return (0);
}

int	init_data_rays(t_game *game)
{

	ft_memset(&game->rays, 0, sizeof(t_ray));
	ft_memset(&game->ray_casts, 0, sizeof(t_ray_cast));

	return (0);
}

int	init_data_player(t_game *game, const char *direction_input)
{
	game->player.width = 1;
	game->player.height = 1;
	game->player.turnDirection = 0;
	game->player.strafeDirection = 0;
	game->player.walkDirection = 0;
	game->player.rotationAngle = PI / 2;
	game->player.walkSpeed = SPEED;
	game->player.turnSpeed = 80 * (PI / 180);
	game->ticksLastFrame = 0;
	if (direction_input != NULL)
		set_player_direction(&game->player, direction_input);
	else
		game->player.rotationAngle = PI / 2;
	return (0);
}

/*
int	init_data_map(t_game *game)
{
	const char	*mapdata[MAP_NUM_ROWS] = {"111111111111111", "100000000000101",
		"100100000000101", "101110000010101", "100000000010101",
		"100000001111101", "100000000000001", "100000000000001",
		"111111000111101", "100000000000001", "111111111111111"};
	int			i;

	game->map = malloc(sizeof(char *) * MAP_NUM_ROWS);
	if (!game->map)
		return ('\0');
	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		game->map[i] = ft_strdup(mapdata[i]);
		if (!game->map[i])
		{
			printf("Error duplicating map row.\n");
			return (-1);
		}
		i++;
		printf("[%d]", i);
	}
	return (0);
}
*/
