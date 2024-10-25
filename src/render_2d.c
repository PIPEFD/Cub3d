/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:24:36 by dbonilla          #+#    #+#             */
/*   Updated: 2024/10/25 15:04:58 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define MINI_W (WINDOW_WIDTH / 5)
# define MINI_H (WINDOW_HEIGHT / 5)

#if MINI_W > MINI_H
    #define MINI_T (MINI_W / 20)
#else
    #define MINI_T (MINI_H / 20)
#endif

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

int draw_circle(t_game *game)
{
    t_rectangle_params *params; // You may want to rename this to circle_params
    int x, y;
    int radius; // Assuming width is the diameter

    params = game->draw_figures.rect_params; // Keep the same struct if it has radius information
    radius = params->width / 2;
	x = -radius - 1;
	while (++x <= radius)
    {
		y = -radius - 1;
        while (++y <= radius)
        {
            if (x * x + y * y <= radius * radius) // Check if the point is within the circle
            {
                int pixel_x = params->x + x;
                int pixel_y = params->y + y;

                if (pixel_x >= 0 && pixel_x < (int)game->img->width &&
                    pixel_y >= 0 && pixel_y < (int)game->img->height)
                    mlx_put_pixel(game->img, pixel_x, pixel_y, params->color);
            }
        }
    }
    return (0);
}

void	render_player(t_game *game)
{
	float			line_length;

	game->draw_figures.rect_params->x = MINI_W / 2;
	game->draw_figures.rect_params->y = MINI_W / 2;
	game->draw_figures.rect_params->width = PLAYER_SIZE;
	game->draw_figures.rect_params->height = PLAYER_SIZE;
	game->draw_figures.rect_params->color = 0xFF0000FF;
	draw_circle(game);
	game->draw_figures.line_params->x0 = MINI_W / 2;
	game->draw_figures.line_params->y0 = MINI_H / 2;
	line_length = 20;
	game->draw_figures.line_params->x1 = game->draw_figures.line_params->x0
		+ cos(game->player.rotationAngle) * line_length;
	game->draw_figures.line_params->y1 = game->draw_figures.line_params->y0
		+ sin(game->player.rotationAngle) * line_length;
	game->draw_figures.line_params->color = 0xFF0000FF;
	//draw_line(game);
}

int is_this_floor(t_game *game, int x, int y)
{
    int map_y;
    int map_x;
    float angle;

    angle = game->player.rotationAngle + PI / 2;
    
    // Ajuste del centro del minimapa
    int center_x = MINI_W / 2;
    int center_y = MINI_W / 2;

    // Calcular las coordenadas relativas al centro
    float rel_x = x - center_x;
    float rel_y = y - center_y;

    // Aplicar la rotación
    float rotated_x = rel_x * cos(angle) - rel_y * sin(angle);
    float rotated_y = rel_x * sin(angle) + rel_y * cos(angle);

    // Ajustar las coordenadas del mapa
    map_x = (int)(rotated_x * 0.05 + game->player.x / TILE_SIZE);
    map_y = (int)(rotated_y * 0.05 + game->player.y / TILE_SIZE);

    // Verificar límites
    if (map_y < 0 || map_y >= split_len(game->map))
        return (0);
    if (map_x < 0 || map_x >= (int)ft_strlen(game->map[map_y]))
        return (0);
    if (game->map[map_y][map_x] == '1')
        return (0);
    
    return (1);
}

void render_map(t_game *game)
{
    int y, x;
    int center_x = MINI_W / 2;
    int center_y = MINI_W / 2;
    int radius = MINI_W / 2; // Aumentar el radio del círculo

    y = 0; // Comenzar desde 0
    while (y < MINI_W)
    {
        x = 0; // Comenzar desde 0
        while (x < MINI_W)
        {
            // Calcular la distancia desde el centro
            int dx = x - center_x;
            int dy = y - center_y;

            // Verificar si el punto está dentro del círculo y si es par
            if (dx * dx + dy * dy <= radius * radius && x % 2 == 0 && y % 2 == 0)
            {
                if (is_this_floor(game, x, y))
                    mlx_put_pixel(game->img, x, y, 0xffffffff);
                else
                    mlx_put_pixel(game->img, x, y, 0x000000ff);
            }
            x++; // Incrementar x
        }
        y++; // Incrementar y
    }
}

/*
void	render_map(t_game *game)
{
	int				i;
	int				j;
	int				tile_x;
	int				tile_y;
	unsigned int	tile_color;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '0' || game->map[i][j] == ' ')
				tile_color = 0x000000FF;
			else
				tile_color = 0xE9E9E9FF;
			tile_x = j * TILE_SIZE;
			tile_y = i * TILE_SIZE;
			game->draw_figures.rect_params->x = tile_x * MINIMAP_SCALE_FACTOR;
			game->draw_figures.rect_params->y = tile_y * MINIMAP_SCALE_FACTOR;
			game->draw_figures.rect_params->width = TILE_SIZE
				* MINIMAP_SCALE_FACTOR;
			game->draw_figures.rect_params->height = TILE_SIZE
				* MINIMAP_SCALE_FACTOR;
			game->draw_figures.rect_params->color = tile_color;
			draw_rectangle(game);
		}
	}
}
*/
