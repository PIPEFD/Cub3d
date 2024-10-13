/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:19:51 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/13 17:37:37 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	direction_to_radians(const char *directionInput)
{
	if (ft_strcmp(directionInput, "N") == 0)
		return (3 * PI / 2);
	if (ft_strcmp(directionInput, "S") == 0)
		return (PI / 2);
	if (ft_strcmp(directionInput, "E") == 0)
		return (0);
	if (ft_strcmp(directionInput, "O") == 0)
		return (PI);
	return (-1);
}

int	set_player_direction(t_player *player, const char *directionInput)
{
	float	degrees;
	float	rotation_angle;

	rotation_angle = direction_to_radians(directionInput);
	if (rotation_angle == -1)
	{
		degrees = atof(directionInput);
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
