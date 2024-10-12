/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:26:49 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/12 01:26:24 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void init_single_ray(t_ray *ray)
{
    ray->distance = 0;
    ray->wallHitX = 0;
    ray->wallHitY = 0;
    ray->wallHitContent = 0;
    ray->wasHitVertical = 0;
    ray->rayAngle = 0;
    ray->isRayFacingDown = 0;
    ray->isRayFacingUp = 0;
    ray->isRayFacingLeft = 0;
    ray->isRayFacingRight = 0;
}
void init_single_ray_cast(t_ray_cast *ray_cast)
{
    ray_cast->isRayFacingDown = 0;
    ray_cast->isRayFacingUp = 0;
    ray_cast->isRayFacingRight = 0;
    ray_cast->isRayFacingLeft = 0;
    ray_cast->xintercept = 0;
    ray_cast->yintercept = 0;
    ray_cast->xstep = 0;
    ray_cast->ystep = 0;
    ray_cast->foundHorzWallhit = 0;
    ray_cast->horWallHitX = 0;
    ray_cast->horWallHitY = 0;
    ray_cast->horWallContent = 0;
    ray_cast->foundVerWallhit = 0;
    ray_cast->verWallHitX = 0;
    ray_cast->verWallHitY = 0;
    ray_cast->verWallContent = 0;
    ray_cast->nextHorzTouchX = 0;
    ray_cast->nextHorzTouchY = 0;
    ray_cast->nextVerTouchX = 0;
    ray_cast->nextVerTouchY = 0;
    ray_cast->horHitDistance = 0;
    ray_cast->verHitDistance = 0;
}
int data_init_rays(t_game *game)
{
    // Iterar sobre todos los rayos y ray_casts
    for (int i = 0; i < NUM_RAYS; i++)
    {
        // Inicializar cada rayo
        init_single_ray(&game->rays[i]);

        // Inicializar cada ray_cast
        init_single_ray_cast(&game->ray_casts[i]);
    }
    return (0);
}


int	init_data_player(t_game *game, const char *direction_input)
{
	game->player.x = WINDOW_WIDTH / 2;
	game->player.y = WINDOW_HEIGHT / 2;
	game->player.width = 1;
	game->player.height = 1;
	game->player.turnDirection = 0;
	game->player.strafeDirection = 0; // Inicializar strafeDirection
	game->player.walkDirection = 0;
	game->player.rotationAngle = PI / 2;
	game->player.walkSpeed = 150;
	game->player.turnSpeed = 45 * (PI / 180);
	game->ticksLastFrame = 0;
	// Establecer la dirección del jugador basada en el input
	if (direction_input != NULL)
	{
		set_player_direction(&game->player, direction_input);
	}
	else
	{
		// Dirección predeterminada si no se proporciona input
		game->player.rotationAngle = PI / 2; // 90 grados
	}
	return (0);
}

int	init_data_map(t_game *game)
{
	const int mapData[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

	// Set up hooks
	game->map = malloc(sizeof(char *) * MAP_NUM_ROWS);
	if (!game->map)
	{
		printf("Error allocating memory for map.\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < MAP_NUM_ROWS; i++)
	{
		game->map[i] = ft_strdup((char *)mapData[i]);
		if (!game->map[i])
		{
			printf("Error duplicating map row.\n");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
