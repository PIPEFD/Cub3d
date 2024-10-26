/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:24:36 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/26 18:31:33 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define MINI_W (WINDOW_WIDTH / 3)
# define MINI_H (WINDOW_HEIGHT / 3)

#if MINI_H > MINI_W
    #define MINI_R (MINI_W / 2)
    #define MINI_T (MINI_W / 20)
#else
    #define MINI_R (MINI_H / 2)
    #define MINI_T (MINI_H / 20)
#endif

/*
void	render_rays(t_game *game)
{
	unsigned int	ray_color;
	int				i;

	ray_color = 0x38FF00FF;
	i = 50;
	while (NUM_RAYS > i)
	{
		game->draw_figures.line_params->x0 = game->player.x
			* MINIMAP_SCALE_FACTOR;
		game->draw_figures.line_params->y0 = game->player.y
			* MINIMAP_SCALE_FACTOR;
		game->draw_figures.line_params->x1 = game->rays[i].wallHitX
			* MINIMAP_SCALE_FACTOR;
		game->draw_figures.line_params->y1 = game->rays[i].wallHitY
			* MINIMAP_SCALE_FACTOR;
		game->draw_figures.line_params->color = ray_color;
		draw_line(game);
		i++;
	}
}
*/

void    draw_player(t_game *game)
{
    int x;
    int y;
    int pixel_x;
    int pixel_y;

	x = -1 - PLAYER_SIZE;
	while (++x < PLAYER_SIZE / 2)
    {
		y = -1 - PLAYER_SIZE;
        while (++y < PLAYER_SIZE / 2)
        {
            if (x * x + y * y <= PLAYER_SIZE / 2 * PLAYER_SIZE / 2)
            {
                pixel_x = MINI_R + x;
                pixel_y = MINI_R + y;
                mlx_put_pixel(game->img, pixel_x, pixel_y, 0xFF0000FF);
            }
        }
    }
}

int is_this_floor(t_game *game, int x, int y)
{
    int map_y;
    int map_x;
    float rotated_x;
    float rotated_y;

    rotated_x = (x - MINI_R) * cos(game->player.rotationAngle + PI / 2);
    rotated_x -= (y - MINI_R) * sin(game->player.rotationAngle + PI / 2);
    rotated_y = (x - MINI_R) * sin(game->player.rotationAngle + PI / 2);
    rotated_y += (y - MINI_R) * cos(game->player.rotationAngle + PI / 2);

    map_x = (int)(rotated_x * 0.05 + game->player.x / TILE_SIZE);
    map_y = (int)(rotated_y * 0.05 + game->player.y / TILE_SIZE);

    if (map_y < 0 || map_y >= split_len(game->map))
        return (0);
    if (map_x < 0 || map_x >= (int)ft_strlen(game->map[map_y]))
        return (0);
    return (game->map[map_y][map_x] == '0');
}

void render_minimap(t_game *game)
{
    int y;
    int x;
    int i;
    int j;

    y = -1;
    while (++y < MINI_R * 2)
    {
        x = -1;
        while (++x < MINI_R * 2)
        {
            i = x - MINI_R;
            j = y - MINI_R;
            if (i * i + j * j <= MINI_R * MINI_R && x % 2 == 0 && y % 2 == 0)
            {
                if (is_this_floor(game, x, y))
                    mlx_put_pixel(game->img, x, y, 0xffffffff);
                else
                    mlx_put_pixel(game->img, x, y, 0x000000ff);
            }
        }
    }
    draw_player(game);
}
