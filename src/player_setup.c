/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:19:51 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/25 17:16:24 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	direction_to_radians(const char direction_input)
{
	if (direction_input == 'S')
		return (3 * PI / 2);
	else if (direction_input == 'N')
		return (PI / 2);
	else if (direction_input == 'E')
		return (0);
	else if (direction_input == 'W')
		return (PI);
	return (-1);
}

int	set_player_direction(t_player *player)
{
	float	rotation_angle;

	rotation_angle = direction_to_radians(player->dir);
	player->rotationAngle = normalize_angle(rotation_angle);
	return (0);
}

void	move_player(t_game *game)
{
	t_player	*player;
	float		movestep;
	float		strafestep;
	float		newplayer_x;
	float		newplayer_y;

	player = &game->player;
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


/*
	if (player->x > newplayer_x)
	{
		if (player->y > newplayer_y)
		{
			if (!map_has_wall_at(game, newplayer_x - SIZE, player->y - SIZE))
				player->x = newplayer_x;
			if (!map_has_wall_at(game, player->x - SIZE, newplayer_y - SIZE))
				player->y = newplayer_y;
		}
		else
		{
			if (!map_has_wall_at(game, newplayer_x - SIZE, player->y + SIZE))
				player->x = newplayer_x;
			if (!map_has_wall_at(game, player->x - SIZE, newplayer_y + SIZE))
				player->y = newplayer_y;
		}
	}
	else
	{
		if (player->y > newplayer_y)
		{
			if (!map_has_wall_at(game, newplayer_x + SIZE, player->y - SIZE))
				player->x = newplayer_x;
			if (!map_has_wall_at(game, player->x + SIZE, newplayer_y - SIZE))
				player->y = newplayer_y;
		}
		else
		{
			if (!map_has_wall_at(game, newplayer_x + SIZE, player->y + SIZE))
				player->x = newplayer_x;
			if (!map_has_wall_at(game, player->x + SIZE, newplayer_y + SIZE))
				player->y = newplayer_y;
		}
	}
*/

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
