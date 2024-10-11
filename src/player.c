/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:19:51 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/11 23:35:21 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	set_player_direction(t_player *player, const char *directionInput)
{
	float	degrees;

	if (ft_strcmp(directionInput, "N") == 0 || ft_strcmp(directionInput, "n") == 0)
	{
		player->rotationAngle = 3 * PI / 2; // 270 grados
	}
	else if (ft_strcmp(directionInput, "S") == 0 || ft_strcmp(directionInput,
			"s") == 0)
	{
		player->rotationAngle = PI / 2; // 90 grados
	}
	else if (ft_strcmp(directionInput, "E") == 0 || ft_strcmp(directionInput,
			"e") == 0)
	{
		player->rotationAngle = 0;
	}
	else if (ft_strcmp(directionInput, "O") == 0 || ft_strcmp(directionInput,
			"o") == 0)
	{
		player->rotationAngle = PI; // 180 grados
	}
	else
	{
		// Intentar convertir el input a grados y luego a radianes
		degrees = atof(directionInput);
		player->rotationAngle = degrees * (PI / 180.0);
	}
	// Normalizar el ángulo entre 0 y 2*PI
	if (player->rotationAngle < 0)
		player->rotationAngle += TWO_PI;
	if (player->rotationAngle >= TWO_PI)
		player->rotationAngle -= TWO_PI;
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
	player->rotationAngle = normalizeAngle(player->rotationAngle);
	movestep = player->walkDirection * player->walkSpeed * deltaTime;
	strafestep = player->strafeDirection * player->walkSpeed * deltaTime;
	newplayer_x = player->x + cos(player->rotationAngle) * movestep
		+ cos(player->rotationAngle + PI / 2) * strafestep;
	newplayer_y = player->y + sin(player->rotationAngle) * movestep
		+ sin(player->rotationAngle + PI / 2) * strafestep;
	if (!mapHasWallAt(game, newplayer_x, newplayer_y))
	{
		player->x = newplayer_x;
		player->y = newplayer_y;
	}
	return (0);
}
