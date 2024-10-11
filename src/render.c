/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:24:36 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/11 00:56:19 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3d.h"


void renderRays(t_game* game)
{
    
    uint32_t rayColor = 0x38FF00FF; // ARGB format
    for(int i = 0; i < NUM_RAYS; i+=50)
    {
        draw_line(
            game->img,
            game->player.x * MINIMAP_SCALE_FACTOR,
            game->player.y * MINIMAP_SCALE_FACTOR,
            game->rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
            game->rays[i].wallHitY * MINIMAP_SCALE_FACTOR,
            rayColor);
    }
}

void renderPlayer(t_game* game)
{
    unsigned int playerColor = 0xFA0000FF; // ARGB format
    draw_rectangle(game->img,
        game->player.x * MINIMAP_SCALE_FACTOR,
        game->player.y * MINIMAP_SCALE_FACTOR,
        game->player.width * MINIMAP_SCALE_FACTOR,
        game->player.height * MINIMAP_SCALE_FACTOR,
        playerColor);
    // Draw line indicating direction
    draw_line(
        game->img,
        game->player.x * MINIMAP_SCALE_FACTOR,
        game->player.y * MINIMAP_SCALE_FACTOR,
        (game->player.x + cos(game->player.rotationAngle) * 40) * MINIMAP_SCALE_FACTOR,
        (game->player.y + sin(game->player.rotationAngle) * 40) * MINIMAP_SCALE_FACTOR,
        playerColor);
}

void renderMap(t_game* game)
{
   for (int i = 0; i < MAP_NUM_ROWS; i++) {
        for (int j = 0; j < MAP_NUM_COLS; j++) {
            int tileX = j * TILE_SIZE;
            int tileY = i * TILE_SIZE;
            unsigned int tileColor = game->map[i][j] != '0' ?  0xE9E9E9FF: 0x000000FF; // ARGB format
            draw_rectangle(game->img,
                tileX * MINIMAP_SCALE_FACTOR,
                tileY * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                tileColor);
        }
    }
}

void render3DProjection(t_game* game)
{
    for (int i = 0; i < NUM_RAYS; i++)
    {
        // Correct the distance for the fish-eye effect
        float perpDistance = game->rays[i].distance * cos(game->rays[i].rayAngle - game->player.rotationAngle);
        // Calculate the distance to the projection plane
        float distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
        // Calculate projected wall height
        float wallStripHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

        // Calculate top and bottom of the wall
        int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

        // Draw the wall
        uint32_t wallColor;
        if (game->rays[i].wasHitVertical)
            wallColor = 0xFFFFFFFF; // White color for vertical walls
        else
            wallColor = 0xCCCCCCFF; // Light gray color for horizontal walls

        for (int y = wallTopPixel; y < wallBottomPixel; y++)
        {
            mlx_put_pixel(game->img, i, y, wallColor);
        }

        // Draw the floor
        for (int y = wallBottomPixel; y < WINDOW_HEIGHT; y++)
        {
            mlx_put_pixel(game->img, i, y, 0x7F7F7FFF); // Dark gray color for floor
        }

        // Draw the ceiling
        for (int y = 0; y < wallTopPixel; y++)
        {
            mlx_put_pixel(game->img, i, y, 0x000000FF); // Black color for ceiling
        }
    }
}