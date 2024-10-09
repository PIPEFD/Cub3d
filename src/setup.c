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


void update(t_player *player, mlx_t *mlx, mlx_image_t *img, t_ray *ray)
{
    // (void)param; // Unused parameter

    // Calculate deltaTime
    unsigned int timeNow = mlx_get_time() * 1000;
    float deltaTime = (timeNow - ticksLastFrame) / 1000.0f;
    ticksLastFrame = timeNow;

    movePlayer(deltaTime, player, mlx, img, ray);
    castAllRays(player, mlx, img, ray);;

    // Clear the image buffer
    memset(img->pixels, 255, img->width * img->height * sizeof(unsigned int));

    // Render functions
    renderMap(player, mlx, img, ray);
    renderRays(player, mlx, img, ray);
    renderPlayer(player, mlx, img, ray);
}

void setup(mlx_t *mlx)
{

    mlx_image_t *img;
    t_player player;
    t_ray ray[NUM_RAYS];

    
    img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img)
    {
        fprintf(stderr, "Error creating image.\n");
        exit(EXIT_FAILURE);
    }
    mlx_image_to_window(mlx, img, 0, 0);

    // Initialize player
    player.x = WINDOW_WIDTH / 2;
    player.y = WINDOW_HEIGHT / 2;

    player.width = 1;
    player.height = 1;
    player.turnDirection = 0;
    player.walkDirection = 0;
    player.rotationAngle = PI / 2;
    player.walkSpeed = 150;
    player.turnSpeed = 45 * (PI / 180);

    // Set up hooks
    mlx_key_hook(mlx, &key_hook, NULL);
    mlx_loop_hook(mlx, &update, NULL);
}

