/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:19:51 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/27 14:21:00 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, t_player *player)
{
	float	movestep;
	float	strafestep;
	float	newplayer_x;
	float	newplayer_y;

	player->rotationAngle += player->turnDirection * player->turnSpeed;
	player->rotationAngle = normalize_angle(player->rotationAngle);
	movestep = player->walkDirection * player->walkSpeed;
	strafestep = player->strafeDirection * player->walkSpeed;
	newplayer_x = player->x + cos(player->rotationAngle) * movestep
		+ cos(player->rotationAngle + PI / 2) * strafestep;
	newplayer_y = player->y + sin(player->rotationAngle) * movestep
		+ sin(player->rotationAngle + PI / 2) * strafestep;
	if (!map_has_wall_at(game, newplayer_x, player->y))
		player->x = newplayer_x;
	if (!map_has_wall_at(game, player->x, newplayer_y))
		player->y = newplayer_y;
}

float	direction_to_radians(const char direction_input)
{
	if (direction_input == 'N')
		return (3 * PI / 2 + 0.003f);
	else if (direction_input == 'S')
		return (PI / 2 + 0.003f);
	else if (direction_input == 'E')
		return (0.003f);
	else if (direction_input == 'W')
		return (PI + 0.003f);
	return (-1);
}

void	set_player_direction(t_player *player)
{
	float	rotation_angle;

	rotation_angle = direction_to_radians(player->dir);
	player->rotationAngle = normalize_angle(rotation_angle);
}

int	init_data_move_player(t_bresenham_vars *vars, t_line_params *params)
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
	return (0);
}

int	get_player_data(t_game *data)
{
	int	y;
	int	x;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (ft_strchr("NSWE", data->map[y][x]))
			{
				if (data->player.dir != 0)
					return (0);
				data->player.x = x * TILE_SIZE + TILE_SIZE / 2;
				data->player.y = y * TILE_SIZE + TILE_SIZE / 2;
				data->player.dir = data->map[y][x];
				data->map[y][x] = '0';
			}
		}
	}
	return (data->player.dir);
}
