/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:34 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/12 21:14:18 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int mapHasWallAt(t_game* game, float x, float y)
{
    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT) {
        return 1;
    }
    int mapGridIndexX = floor(x / TILE_SIZE);
    int mapGridIndexY = floor(y / TILE_SIZE);

    // Asegurarse de que los índices están dentro de los límites del mapa
    if (mapGridIndexY < 0 || mapGridIndexY >= MAP_NUM_ROWS ||
        mapGridIndexX < 0 || mapGridIndexX >= MAP_NUM_COLS)
    {
        return 1;
    }

    char tile = game->map[mapGridIndexY][mapGridIndexX];
    return tile != '0';
}

