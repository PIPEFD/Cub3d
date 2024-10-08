/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:24:36 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/08 16:27:45 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3d.h"
void renderRays()
{
    uint32_t rayColor = 0x38FF00FF; // ARGB format
    for(int i = 0; i < NUM_RAYS; i++)
    {
        draw_line(
            img,
            player.x * MINIMAP_SCALE_FACTOR,
            player.y * MINIMAP_SCALE_FACTOR,
            ray[i].wallHitX * MINIMAP_SCALE_FACTOR,
            ray[i].wallHitY * MINIMAP_SCALE_FACTOR,
            rayColor);
    }
}

void renderMap()
{
    for (int i = 0; i < MAP_NUM_ROWS; i++) {
        for (int j = 0; j < MAP_NUM_COLS; j++) {
            int tileX = j * TILE_SIZE;
            int tileY = i * TILE_SIZE;
            uint32_t tileColor = map[i][j] != 0 ? 0x000000FF : 0xE9E9E9FF; // ARGB format
            draw_rectangle(img,
                tileX * MINIMAP_SCALE_FACTOR,
                tileY * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                tileColor);
        }
    }
}

