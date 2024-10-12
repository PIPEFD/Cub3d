/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:21:08 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/13 00:51:18 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void cast_ray(t_game* game, float rayAngle, int stripid) {
    rayAngle = normalize_angle(rayAngle);

    t_player* player = &game->player;
    t_ray* rays = game->rays;

    t_ray_cast* ray_cast = &game->ray_casts[stripid];

    ray_cast->isRayFacingDown = rayAngle > 0 && rayAngle < PI;
    ray_cast->isRayFacingUp = !ray_cast->isRayFacingDown;
    ray_cast->isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    ray_cast->isRayFacingLeft = !ray_cast->isRayFacingRight;


    ray_cast->foundHorzWallhit = 0;
    ray_cast->horWallHitX = 0;
    ray_cast->horWallHitY = 0;
    ray_cast->horWallContent = 0;

    ray_cast->yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    ray_cast->yintercept += ray_cast->isRayFacingDown ? TILE_SIZE : 0;

    ray_cast->xintercept = player->x + (ray_cast->yintercept - player->y) / tan(rayAngle);

    ray_cast->ystep = TILE_SIZE;
    ray_cast->ystep *= ray_cast->isRayFacingUp ? -1 : 1;

    ray_cast->xstep = TILE_SIZE / tan(rayAngle);
    ray_cast->xstep *= (ray_cast->isRayFacingLeft && ray_cast->xstep > 0) ? -1 : 1;
    ray_cast->xstep *= (ray_cast->isRayFacingRight && ray_cast->xstep < 0) ? -1 : 1;

    ray_cast->nextHorzTouchX = ray_cast->xintercept;
    ray_cast->nextHorzTouchY = ray_cast->yintercept;

    while (ray_cast->nextHorzTouchX >= 0 && ray_cast->nextHorzTouchX <= WINDOW_WIDTH &&
           ray_cast->nextHorzTouchY >= 0 && ray_cast->nextHorzTouchY <= WINDOW_HEIGHT) {
        float xToCheck = ray_cast->nextHorzTouchX;
        float yToCheck = ray_cast->nextHorzTouchY + (ray_cast->isRayFacingUp ? -1 : 0);

        if (map_has_wall_at(game, xToCheck, yToCheck)) {
            ray_cast->horWallHitX = ray_cast->nextHorzTouchX;
            ray_cast->horWallHitY = ray_cast->nextHorzTouchY;
            ray_cast->horWallContent = game->map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            ray_cast->foundHorzWallhit = 1;
            break;
        } else {
            ray_cast->nextHorzTouchX += ray_cast->xstep;
            ray_cast->nextHorzTouchY += ray_cast->ystep;
        }
    }

    // Intersección vertical
    ray_cast->foundVerWallhit = 0;
    ray_cast->verWallHitX = 0;
    ray_cast->verWallHitY = 0;
    ray_cast->verWallContent = 0;

    ray_cast->xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    ray_cast->xintercept += ray_cast->isRayFacingRight ? TILE_SIZE : 0;

    ray_cast->yintercept = player->y + (ray_cast->xintercept - player->x) * tan(rayAngle);

    ray_cast->xstep = TILE_SIZE;
    ray_cast->xstep *= ray_cast->isRayFacingLeft ? -1 : 1;

    ray_cast->ystep = TILE_SIZE * tan(rayAngle);
    ray_cast->ystep *= (ray_cast->isRayFacingUp && ray_cast->ystep > 0) ? -1 : 1;
    ray_cast->ystep *= (ray_cast->isRayFacingDown && ray_cast->ystep < 0) ? -1 : 1;

    ray_cast->nextVerTouchX = ray_cast->xintercept;
    ray_cast->nextVerTouchY = ray_cast->yintercept;

    while (ray_cast->nextVerTouchX >= 0 && ray_cast->nextVerTouchX <= WINDOW_WIDTH &&
           ray_cast->nextVerTouchY >= 0 && ray_cast->nextVerTouchY <= WINDOW_HEIGHT) {
        float xToCheck = ray_cast->nextVerTouchX + (ray_cast->isRayFacingLeft ? -1 : 0);
        float yToCheck = ray_cast->nextVerTouchY;

        if (map_has_wall_at(game, xToCheck, yToCheck)) {
            ray_cast->verWallHitX = ray_cast->nextVerTouchX;
            ray_cast->verWallHitY = ray_cast->nextVerTouchY;
            ray_cast->verWallContent = game->map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            ray_cast->foundVerWallhit = 1;
            break;
        } else {
            ray_cast->nextVerTouchX += ray_cast->xstep;
            ray_cast->nextVerTouchY += ray_cast->ystep;
        }
    }

    // Calculamos las distancias
    ray_cast->horHitDistance = (ray_cast->foundHorzWallhit)
        ? distance_between_points(player->x, player->y, ray_cast->horWallHitX, ray_cast->horWallHitY)
        : FLT_MAX;
    ray_cast->verHitDistance = (ray_cast->foundVerWallhit)
        ? distance_between_points(player->x, player->y, ray_cast->verWallHitX, ray_cast->verWallHitY)
        : FLT_MAX;

    // Determinamos el impacto más cercano
    if (ray_cast->verHitDistance < ray_cast->horHitDistance) {
        rays[stripid].distance = ray_cast->verHitDistance;
        rays[stripid].wallHitX = ray_cast->verWallHitX;
        rays[stripid].wallHitY = ray_cast->verWallHitY;
        rays[stripid].wallHitContent = ray_cast->verWallContent;
        rays[stripid].wasHitVertical = 1;
    } else {
        rays[stripid].distance = ray_cast->horHitDistance;
        rays[stripid].wallHitX = ray_cast->horWallHitX;
        rays[stripid].wallHitY = ray_cast->horWallHitY;
        rays[stripid].wallHitContent = ray_cast->horWallContent;
        rays[stripid].wasHitVertical = 0;
    }

    // Asignamos las propiedades del rayo
    rays[stripid].rayAngle = rayAngle;
    rays[stripid].isRayFacingDown = ray_cast->isRayFacingDown;
    rays[stripid].isRayFacingUp = ray_cast->isRayFacingUp;
    rays[stripid].isRayFacingLeft = ray_cast->isRayFacingLeft;
    rays[stripid].isRayFacingRight = ray_cast->isRayFacingRight;
}

void cast_all_rays(t_game* game)
{

    float rayAngle = game->player.rotationAngle - (FOV / 2);
    for (int stripid = 0; stripid < NUM_RAYS; stripid++)
    {
        cast_ray(game, rayAngle, stripid);
        rayAngle += FOV / NUM_RAYS;
    }
}
