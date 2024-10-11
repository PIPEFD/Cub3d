/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/10 16:18:28 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

extern const int map[MAP_NUM_ROWS][MAP_NUM_COLS];

void castRay(t_game* game, float rayAngle, int stripid)
{
    rayAngle = normalizeAngle(rayAngle);

    t_player* player = &game->player;
    t_ray* rays = game->rays;

    int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;
    float xstep;
    float ystep;
    float xintercept;
    float yintercept;

    int foundHorzWallhit = 0;
    float horWallHitX = 0;
    float horWallHitY = 0;
    int horWallContent = 0;

    yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDown ? TILE_SIZE : 0;

    xintercept = player->x + (yintercept - player->y) / tan(rayAngle);

    ystep = TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(rayAngle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    while(nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH &&  nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT)
    {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

        if(mapHasWallAt(game, xToCheck, yToCheck))
        {
            horWallHitX = nextHorzTouchX;
            horWallHitY = nextHorzTouchY;
            horWallContent = game->map[(int)floor(yToCheck / TILE_SIZE)] [(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallhit = 1;
            break;
        }
        else
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }

    int foundVerWallhit = 0;
    float verWallHitX = 0;
    float verWallHitY = 0;
    int verWallContent = 0;

    xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    yintercept = player->y + (xintercept - player->x) * tan(rayAngle);

    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(rayAngle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVerTouchX = xintercept;
    float nextVerTouchY = yintercept;

    while(nextVerTouchX >= 0 && nextVerTouchX <= WINDOW_WIDTH &&  nextVerTouchY >= 0 && nextVerTouchY <= WINDOW_HEIGHT)
    {
        float xToCheck = nextVerTouchX + (isRayFacingLeft ? -1: 0);
        float yToCheck = nextVerTouchY;

        if(mapHasWallAt(game, xToCheck, yToCheck))
        {
            verWallHitX = nextVerTouchX;
            verWallHitY = nextVerTouchY;
            verWallContent = game->map[(int)floor(yToCheck / TILE_SIZE)] [(int)floor(xToCheck / TILE_SIZE)];
            foundVerWallhit  = 1;
            break;
        }
        else
        {
            nextVerTouchX += xstep;
            nextVerTouchY += ystep;
        }
    }

    float horHitDistance =  (foundHorzWallhit)
    ? distanceBetweenPoints(player->x, player->y, horWallHitX, horWallHitY)
    : FLT_MAX;
    float verHitDistance = (foundVerWallhit)
        ? distanceBetweenPoints(player->x, player->y, verWallHitX, verWallHitY)
        : FLT_MAX;
    if (verHitDistance < horHitDistance)
    {
        rays[stripid].distance = verHitDistance;
        rays[stripid].wallHitX = verWallHitX;
        rays[stripid].wallHitY = verWallHitY;
        rays[stripid].wallHitContent = verWallContent;
        rays[stripid].wasHitVertical = 1;
    }
    else
    {
        rays[stripid].distance = horHitDistance;
        rays[stripid].wallHitX = horWallHitX;
        rays[stripid].wallHitY = horWallHitY;
        rays[stripid].wallHitContent = horWallContent;
        rays[stripid].wasHitVertical = 0;
    }
    rays[stripid].rayAngle = rayAngle;
    rays[stripid].isRayFacingDown = isRayFacingDown;
    rays[stripid].isRayFacingUp = isRayFacingUp;
    rays[stripid].isRayFacingLeft = isRayFacingLeft;
    rays[stripid].isRayFacingRight = isRayFacingRight;
}


void castAllRays(t_game* game)
{
   
    float rayAngle = game->player.rotationAngle - (FOV / 2);
    for (int stripid = 0; stripid < NUM_RAYS; stripid++)
    {
        castRay(game, rayAngle, stripid);
        rayAngle += FOV / NUM_RAYS;
    }
}