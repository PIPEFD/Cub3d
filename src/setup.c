/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:49:01 by dbonilla          #+#    #+#             */
/*   Updated: 2024/09/25 21:49:01 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "../inc/cub3d.h"


void update(void* param)
{
    t_game* game = (t_game*)param;

    // Calculate deltaTime
    unsigned int timeNow = mlx_get_time() * 1000;
    float deltaTime = (timeNow - game->ticksLastFrame) / 1000.0f;
    game->ticksLastFrame = timeNow;

    movePlayer(game, deltaTime);
    castAllRays(game);

    // Clear the image buffer
    memset(game->img->pixels, 0, game->img->width * game->img->height * sizeof(unsigned int));

    // Render functions
    render3DProjection(game);
    renderMap(game);
    renderRays(game);
    renderPlayer(game);
}

void setup(t_game* game)
{
    game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Raycaster", true);
    if (!game->mlx)
    {
        fprintf(stderr, "Error initializing MLX.\n");
        exit(EXIT_FAILURE);
    }
    game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!game->img)
    {
        fprintf(stderr, "Error creating image.\n");
        exit(EXIT_FAILURE);
    }
    mlx_image_to_window(game->mlx, game->img, 0, 0);

    // Initialize player
    game->player.x = WINDOW_WIDTH / 2;
    game->player.y = WINDOW_HEIGHT / 2;

    game->player.width = 1;
    game->player.height = 1;
    game->player.turnDirection = 0;
    game->player.walkDirection = 0;
    game->player.rotationAngle = PI / 2;
    game->player.walkSpeed = 150;
    game->player.turnSpeed = 45 * (PI / 180);

    game->ticksLastFrame = 0;
    const char* mapData[MAP_NUM_ROWS] = {
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
        "111111111111111"
    };
    // Set up hooks
    game->map = malloc(sizeof(char*) * MAP_NUM_ROWS);
    if (!game->map)
    {
        fprintf(stderr, "Error allocating memory for map.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAP_NUM_ROWS; i++)
    {
        game->map[i] = strdup(mapData[i]);
        if (!game->map[i])
        {
            fprintf(stderr, "Error duplicating map row.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Configurar hooks
    mlx_key_hook(game->mlx, &key_hook, game);
    mlx_loop_hook(game->mlx, &update, game);
}

