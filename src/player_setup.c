/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:19:51 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/16 12:38:44 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	direction_to_radians(const char *direction_input)
{
	if (ft_strcmp(direction_input, "N") == 0)
		return (3 * PI / 2);
	if (ft_strcmp(direction_input, "S") == 0)
		return (PI / 2);
	if (ft_strcmp(direction_input, "E") == 0)
		return (0);
	if (ft_strcmp(direction_input, "O") == 0)
		return (PI);
	return (-1);
}

int	set_player_direction(t_player *player, const char *direction_input)
{
	float	degrees;
	float	rotation_angle;

	rotation_angle = direction_to_radians(direction_input);
	if (rotation_angle == -1)
	{
		degrees = atof(direction_input);
		// Cambiar Funcion ATOF -------------------------------------------------------------------
		// -------------------------------------------------------------------
		rotation_angle = degrees * (PI / 180.0);
	}
	player->rotationAngle = normalize_angle(rotation_angle);
	return (0);
}

int	move_player(t_game *game, float deltaTime)
{
	t_player	*player;
	float		movestep;
	float		strafestep;
	float		newplayer_x;
	float		newplayer_y;

	player = &game->player;
	player->rotationAngle += player->turnDirection * player->turnSpeed
		* deltaTime;
	player->rotationAngle = normalize_angle(player->rotationAngle);
	movestep = player->walkDirection * player->walkSpeed * deltaTime;
	strafestep = player->strafeDirection * player->walkSpeed * deltaTime;
	newplayer_x = player->x + cos(player->rotationAngle) * movestep
		+ cos(player->rotationAngle + PI / 2) * strafestep;
	newplayer_y = player->y + sin(player->rotationAngle) * movestep
		+ sin(player->rotationAngle + PI / 2) * strafestep;
	if (!map_has_wall_at(game, newplayer_x, newplayer_y))
	{
		player->x = newplayer_x;
		player->y = newplayer_y;
	}
	return (0);
}

int	init_data_move_player(t_bresenham_vars *vars, t_line_params *params)
{
	vars->x0 = params->x0;
	vars->y0 = params->y0;
	vars->x1 = params->x1;
	vars->y1 = params->y1;
	vars->dx = abs(vars->x1 - vars->x0);
	vars->dy = -abs(vars->y1 - vars->y0);
	vars->sx = (vars->x0 < vars->x1) ? 1 : -1;
	vars->sy = (vars->y0 < vars->y1) ? 1 : -1;
	vars->err = vars->dx + vars->dy;
	return (0);
}
