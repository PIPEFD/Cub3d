/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/08 16:29:19 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void castRay(float rayAngle, int stripid)
{
    rayAngle = normalizeAngle(rayAngle);

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

    yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDown ? TILE_SIZE : 0;

    xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

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

        if(mapHasWallAt(xToCheck, yToCheck))
        {
            horWallHitX = nextHorzTouchX;
            horWallHitY = nextHorzTouchY;
            horWallContent = map[(int)floor(yToCheck / TILE_SIZE)] [(int)floor(xToCheck / TILE_SIZE)];
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

    xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    yintercept = player.y + (xintercept - player.x) * tan(rayAngle);

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

        if(mapHasWallAt(xToCheck, yToCheck))
        {
            verWallHitX = nextVerTouchX;
            verWallHitY = nextVerTouchY;
            verWallContent = map[(int)floor(yToCheck / TILE_SIZE)] [(int)floor(xToCheck / TILE_SIZE)];
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
    ? distanceBetweenPoints(player.x, player.y, horWallHitX, horWallHitY)
    : FLT_MAX;
    float verHitDistance = (foundVerWallhit)
        ? distanceBetweenPoints(player.x, player.y, verWallHitX, verWallHitY)
        : FLT_MAX;
    if (verHitDistance < horHitDistance)
    {
        ray[stripid].distance = verHitDistance;
        ray[stripid].wallHitX = verWallHitX;
        ray[stripid].wallHitY = verWallHitY;
        ray[stripid].wallHitContent = verWallContent;
        ray[stripid].wasHitVertical = 1;
    }
    else
    {
        ray[stripid].distance = horHitDistance;
        ray[stripid].wallHitX = horWallHitX;
        ray[stripid].wallHitY = horWallHitY;
        ray[stripid].wallHitContent = horWallContent;
        ray[stripid].wasHitVertical = 0;
    }
    ray[stripid].rayAngle = rayAngle;
    ray[stripid].isRayFacingDown = isRayFacingDown;
    ray[stripid].isRayFacingUp = isRayFacingUp;
    ray[stripid].isRayFacingLeft = isRayFacingLeft;
    ray[stripid].isRayFacingRight = isRayFacingRight;
}


void castAllRays()
{
    float rayAngle = player.rotationAngle - (FOV / 2);
    for (int stripid = 0; stripid < NUM_RAYS; stripid++)
    {
        castRay(rayAngle, stripid);
        rayAngle += FOV / NUM_RAYS;
    }
}