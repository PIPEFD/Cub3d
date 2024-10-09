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

#include "../inc/cub3d.h"

int main()
{
    mlx_t   *mlx;
    
    mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Raycaster", true);
    if (!mlx)
    {
        fprintf(stderr, "Error initializing MLX.\n");
        exit(EXIT_FAILURE);
    }
    setup(mlx);

    mlx_loop(mlx);

    // destroyWindow();

    return 0;
}