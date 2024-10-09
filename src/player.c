/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:19:51 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/09 15:27:26 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3d.h"


void movePlayer(float deltaTime, t_player *player, mlx_t *mlx, mlx_image_t *img, t_ray *ray)
{
    (void)mlx;
    (void)img;
    (void)ray;
    player->rotationAngle += player->turnDirection * player->turnSpeed * deltaTime;
    player->rotationAngle = fmod(player->rotationAngle, TWO_PI);
    if (player->rotationAngle < 0)
        player->rotationAngle += TWO_PI;

    float moveStep = player->walkDirection * player->walkSpeed * deltaTime;

    float newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
    float newPlayerY = player->y + sin(player->rotationAngle) * moveStep;
    if (!mapHasWallAt(newPlayerX, newPlayerY)) {
        player->x = newPlayerX;
        player->y = newPlayerY;
    }
}


