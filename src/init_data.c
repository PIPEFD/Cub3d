/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:26:49 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/11 23:36:55 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


int data_init_rays(t_game *game) {
    // Inicializamos los rayos
    for (int i = 0; i < NUM_RAYS; i++) {
        // Inicializamos t_ray
        game->rays[i].distance = 0;
        game->rays[i].wallHitX = 0;
        game->rays[i].wallHitY = 0;
        game->rays[i].wallHitContent = 0;
        game->rays[i].wasHitVertical = 0;
        game->rays[i].rayAngle = 0;
        game->rays[i].isRayFacingDown = 0;
        game->rays[i].isRayFacingUp = 0;
        game->rays[i].isRayFacingLeft = 0;
        game->rays[i].isRayFacingRight = 0;

        // Inicializamos t_ray_cast si lo has añadido a t_game
        game->ray_casts[i].isRayFacingDown = 0;
        game->ray_casts[i].isRayFacingUp = 0;
        game->ray_casts[i].isRayFacingRight = 0;
        game->ray_casts[i].isRayFacingLeft = 0;

        game->ray_casts[i].xintercept = 0;
        game->ray_casts[i].yintercept = 0;
        game->ray_casts[i].xstep = 0;
        game->ray_casts[i].ystep = 0;

        game->ray_casts[i].foundHorzWallhit = 0;
        game->ray_casts[i].horWallHitX = 0;
        game->ray_casts[i].horWallHitY = 0;
        game->ray_casts[i].horWallContent = 0;

        game->ray_casts[i].foundVerWallhit = 0;
        game->ray_casts[i].verWallHitX = 0;
        game->ray_casts[i].verWallHitY = 0;
        game->ray_casts[i].verWallContent = 0;

        game->ray_casts[i].nextHorzTouchX = 0;
        game->ray_casts[i].nextHorzTouchY = 0;
        game->ray_casts[i].nextVerTouchX = 0;
        game->ray_casts[i].nextVerTouchY = 0;

        game->ray_casts[i].horHitDistance = 0;
        game->ray_casts[i].verHitDistance = 0;
    }
	return(0);
}


int init_data_player(t_game *game, const char* direction_input)
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

	return(0);
}

int init_data_map(t_game *game)
{
	const char *mapData[MAP_NUM_ROWS] = {
        "111111111111111",
        "100000000000101",
        "100100000000101",
        "101110000010101",
        "100000000010101",
        "100000001111101",
        "100000000000001",
        "100000000000001",
        "111111000111101",
        "100000000000001",
        "111111111111111"};
    // Set up hooks
    game->map = malloc(sizeof(char *) * MAP_NUM_ROWS);
    if (!game->map)
    {
        printf("Error allocating memory for map.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAP_NUM_ROWS; i++)
    {
        game->map[i] = strdup(mapData[i]);
        if (!game->map[i])
        {
            printf("Error duplicating map row.\n");
            exit(EXIT_FAILURE);
        }
    }
	return(0);
}

