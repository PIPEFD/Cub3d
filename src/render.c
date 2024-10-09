/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:24:36 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/09 15:40:05 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3d.h"
void renderRays(t_player *player, mlx_t *mlx, mlx_image_t *img, t_ray *ray)
{
    (void)mlx;
    (void)ray;
    uint32_t rayColor = 0x38FF00FF; // ARGB format
    for(int i = 0; i < NUM_RAYS; i++)
    {
        draw_line(
            img,
            player->x * MINIMAP_SCALE_FACTOR,
            player->y * MINIMAP_SCALE_FACTOR,
            ray[i]->wallHitX * MINIMAP_SCALE_FACTOR,
            ray[i]->wallHitY * MINIMAP_SCALE_FACTOR,
            rayColor);
    }
}

void renderPlayer(t_player *player, mlx_t *mlx, mlx_image_t *img, t_ray *ray)
{
    (void)mlx;
    (void)ray;
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

void renderMap(t_player *player, mlx_t *mlx, mlx_image_t *img, t_ray *ray)
{
    (void)ray;
    (void)mlx;
    (void)player;
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

