/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:19:51 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/10 16:14:18 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3d.h"
extern const int map[MAP_NUM_ROWS][MAP_NUM_COLS];


void movePlayer(t_game  *game, float deltaTime)
{
    t_player    *player = &game->player;

    player->rotationAngle += player->turnDirection * player->turnSpeed * deltaTime;
    player->rotationAngle = fmod(player->rotationAngle, TWO_PI);
    if (player->rotationAngle < 0)
        player->rotationAngle += TWO_PI;

    float moveStep = player->walkDirection * player->walkSpeed * deltaTime;

    float newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
    float newPlayerY = player->y + sin(player->rotationAngle) * moveStep;
    if (!mapHasWallAt(game, newPlayerX, newPlayerY)) {
        player->x = newPlayerX;
        player->y = newPlayerY;
    }
}


