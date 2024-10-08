/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:19:51 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/08 17:52:08 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3d.h"


void movePlayer(float deltaTime)
{
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


void renderPlayer(t_player *player)
{
    unsigned int playerColor = 0xFA0000FF; // ARGB format
    draw_rectangle(img,
        player->x * MINIMAP_SCALE_FACTOR,
        player->y * MINIMAP_SCALE_FACTOR,
        player->width * MINIMAP_SCALE_FACTOR,
        player->height * MINIMAP_SCALE_FACTOR,
        playerColor);
    // Draw line indicating direction
    draw_line(
        img,
        player->x * MINIMAP_SCALE_FACTOR,
        player->y * MINIMAP_SCALE_FACTOR,
        (player->x + cos(player->rotationAngle) * 40) * MINIMAP_SCALE_FACTOR,
        (player->y + sin(player->rotationAngle) * 40) * MINIMAP_SCALE_FACTOR,
        playerColor);
}