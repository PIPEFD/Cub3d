/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:30:31 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/29 14:12:18 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

// Harcodeo de informacion del mapa //

# define FRAMES 30
# define SPEED 25
# define TURN_SPEED 5
# define TILE_SIZE 100
# define WINDOW_WIDTH 2000
# define WINDOW_HEIGHT 1000
# define NUM_RAYS WINDOW_WIDTH
# define PLAYER_SIZE 10


# define MINI_W (WINDOW_WIDTH / 3)
# define MINI_H (WINDOW_HEIGHT / 3)

# if MINI_H > MINI_W
#  define MINI_R (MINI_W / 2)
#  define MINI_T (MINI_W / 20)
# else
#  define MINI_R (MINI_H / 2)
#  define MINI_T (MINI_H / 20)
# endif
// --- // --- // --- // --- // --- //
#define FLOAT_MAX 3.402823466e+38F

# define PI 3.14159265
# define FOV (60 * (PI / 180))
# define FRAME_TIME_LENGTH (1000 / 60) // 60 frames per second

#endif // DEFS_H
