/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:56:38 by pipe              #+#    #+#             */
/*   Updated: 2024/10/25 16:44:35 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_strip(t_game *game, t_texture *text, int x)
{
	int y;
	int	anti_y;
	int	image_x;
	int	image_y;

	//ft_printf("X: %d\n", x);
	//ft_printf("WIDTH: %p\n", text->width2);
	//ft_printf("TOP: %d\n", game->render_params.wall_top_pixel);
	//ft_printf("BOT: %d\n", game->render_params.wall_bottom_pixel);
	//ft_printf("WIN: %d\n", WINDOW_HEIGHT);
	y = 0;
	while (y < game->render_params.wall_top_pixel)
			game->strip[y++] = game->ceiling;
	image_x = 1;
	if (x != 1)
		image_x = (x * text->width2) / TILE_SIZE;
	anti_y = y;
	if (game->render_params.wall_top_pixel < 0)
		anti_y += game->render_params.wall_top_pixel;
	while (y < game->render_params.wall_bottom_pixel && y < WINDOW_HEIGHT)
	{
		image_y = ((y - anti_y) * text->height) / (game->render_params.wall_bottom_pixel - game->render_params.wall_top_pixel);
		if (image_y >= 0 && image_y < text->height && image_x >= 0 && image_x < text->width2)
			game->strip[y] = text->img[image_y][image_x];
		y++;
	}
	while (y < WINDOW_HEIGHT)
		game->strip[y++] = game->floor;
}

int	init_data_render(t_game *game, int i)
{
	// ft_memset(&game->render_params, 0, sizeof(t_render_params));
	game->render_params.perp_distance = game->rays[i].distance
		* cos(game->rays[i].rayAngle - game->player.rotationAngle);
	game->render_params.distance_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	game->render_params.wall_strip_height = (TILE_SIZE
			/ game->render_params.perp_distance)
		* game->render_params.distance_proj_plane;
	game->render_params.wall_top_pixel = (WINDOW_HEIGHT / 2)
		- (game->render_params.wall_strip_height / 2);
	//game->render_params.wall_top_pixel = game->render_params.wall_top_pixel < 0 ? 0 : game->render_params.wall_top_pixel;
	game->render_params.wall_bottom_pixel = (WINDOW_HEIGHT / 2)
		+ (game->render_params.wall_strip_height / 2);
	//game->render_params.wall_bottom_pixel = game->render_params.wall_bottom_pixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : game->render_params.wall_bottom_pixel;
	if (!game->rays[i].wasHitVertical)
	{
		if (game->rays[i].rayAngle < PI && game->rays[i].rayAngle > 0)
			get_strip(game, game->no, (int)(game->rays[i].wallHitX + game->rays[i].wallHitY) % TILE_SIZE);
		else
			get_strip(game, game->so, TILE_SIZE - 1 - ((int)(game->rays[i].wallHitX + game->rays[i].wallHitY) % TILE_SIZE));
	}
	else
	{
		if (game->rays[i].rayAngle > PI * 1/2 && game->rays[i].rayAngle < PI * 3/2)
			get_strip(game, game->we, TILE_SIZE - 1 - ((int)(game->rays[i].wallHitX + game->rays[i].wallHitY) % TILE_SIZE));
		else
			get_strip(game, game->ea, (int)(game->rays[i].wallHitX + game->rays[i].wallHitY) % TILE_SIZE);
	}
	/*
	else if (game->ray_casts[i].isRayFacingLeft)
	else if (game->ray_casts[i].isRayFacingRight)
		get_strip(game, game->we, (int)game->rays[i].wallHitX % TILE_SIZE + (int)game->rays[i].wallHitY % TILE_SIZE);
	*/
	return (0);
}
/*
void	render_wall_strip(t_game *game, int i)
{
	int	y;

	y = game->render_params.wall_top_pixel;
	while (y < game->render_params.wall_bottom_pixel)
	{
		mlx_put_pixel(game->img, i, y, game->render_params.wall_color);
		y++;
	}
}

void	render_floor_and_ceiling(t_game *game, int  i)
{
	int	y;

	// Renderizar techo
	y = 0;
	while (y < game->render_params.wall_top_pixel)
	{
		mlx_put_pixel(game->img, i, y, game->ceiling);
		y++;
	}
	// Renderizar suelo
	y = game->render_params.wall_bottom_pixel;
	while (y < WINDOW_HEIGHT)
	{
		mlx_put_pixel(game->img, i, y, game->floor);
		y++;
	}
}
*/


void	render_strip(t_game *game, int x)
{
	int	y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
		mlx_put_pixel(game->img, x, y, game->strip[y]);
}

void	render_3d_projection(t_game *game)
{
	int index_ray;

	index_ray = 0;
	while (index_ray < NUM_RAYS)
	{
		init_data_render(game, index_ray);
		render_strip(game, index_ray);
		//render_wall_strip(game, index_ray);
		//render_floor_and_ceiling(game, index_ray);
		index_ray++;
	}
	/*
	printf("// --- // --- // --- // --- // --- //\n");
	printf("\nData initialized render correctly\n");
	printf("// --- // --- // --- // --- // --- //\n");
	printf("perp_distance: %f\n", game->render_params.perp_distance);
	printf("distance_proj_plane: %f\n", game->render_params.distance_proj_plane);
	printf("wall_strip_height: %f\n", game->render_params.wall_strip_height);
	printf("wall_top_pixel: %d\n", game->render_params.wall_top_pixel);
	printf("wall_bottom_pixel: %d\n", game->render_params.wall_bottom_pixel);
	*/
}
