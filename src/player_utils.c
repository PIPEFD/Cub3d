/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:19:51 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/12 01:14:58 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float direction_to_radians(const char *directionInput)
{
    if (ft_strcmp(directionInput, "N") == 0 || ft_strcmp(directionInput, "n") == 0)
        return 3 * PI / 2; // 270 grados
    else if (ft_strcmp(directionInput, "S") == 0 || ft_strcmp(directionInput, "s") == 0)
        return PI / 2; // 90 grados
    else if (ft_strcmp(directionInput, "E") == 0 || ft_strcmp(directionInput, "e") == 0)
        return 0; // 0 grados
    else if (ft_strcmp(directionInput, "O") == 0 || ft_strcmp(directionInput, "o") == 0)
        return PI; // 180 grados
    return -1; // Dirección no válida
}


int set_player_direction(t_player *player, const char *directionInput)
{
    float degrees;
    float rotationAngle;

    // Intentar obtener el ángulo de la dirección cardinal
    rotationAngle = direction_to_radians(directionInput);

    // Si la dirección no es válida, intentar convertir el input a grados
    if (rotationAngle == -1)
    {
        degrees = atof(directionInput);
        rotationAngle = degrees * (PI / 180.0); // Convertir grados a radianes
    }

    // Normalizar el ángulo entre 0 y 2*PI
    player->rotationAngle = normalizeAngle(rotationAngle);

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
