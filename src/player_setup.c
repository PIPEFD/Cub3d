/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:19:51 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/13 21:29:41 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	direction_to_radians(const char *direction_input)
{
	if (ft_strcmp(direction_input, "N") == 0 || ft_strcmp(direction_input,
			"n") == 0)
		return (3 * PI / 2);
	else if (ft_strcmp(direction_input, "S") == 0 || ft_strcmp(direction_input,
			"s") == 0)
		return (PI / 2);
	else if (ft_strcmp(direction_input, "E") == 0 || ft_strcmp(direction_input,
			"e") == 0)
		return (0);
	else if (ft_strcmp(direction_input, "O") == 0 || ft_strcmp(direction_input,
			"o") == 0)
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
