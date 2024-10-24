/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:30:31 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/24 19:37:28 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

// Harcodeo de informacion del mapa //
# define FRAMES 30
# define SPEED 10
# define TURN_SPEED 2
# define TILE_SIZE 100
# define WINDOW_WIDTH 2000
# define WINDOW_HEIGHT 1000
# define NUM_RAYS WINDOW_WIDTH
# define PLAYER_SIZE 10 // Tamaño del jugador en píxeles en el minimapa

// --- // --- // --- // --- // --- //
# define MINIMAP_SCALE_FACTOR 0.3
# define PI 3.14159265
# define TWO_PI (2 * PI)
# define FOV (60 * (PI / 180))
# define FRAME_TIME_LENGTH (1000 / 60) // 60 frames per second

#endif //DEFS_H