/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:34:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/30 14:38:46 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(char **map, int x, int y)
{
	int	end;

	if (x < 0 || y < 0 || !map[y] || !map[y][x] || map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1')
		return (0);
	map[y][x] = '1';
	end = 0;
	end |= flood_fill(map, x + 1, y);
	end |= flood_fill(map, x - 1, y);
	end |= flood_fill(map, x, y + 1);
	end |= flood_fill(map, x, y - 1);
	return (end);
}

uint32_t	get_color(uint8_t *p)
{
	uint32_t	b;
	uint32_t	g;
	uint32_t	r;
	uint32_t	a;

	r = (uint32_t) * (p);
	g = (uint32_t) * (p + 1);
	b = (uint32_t) * (p + 2);
	a = (uint32_t) * (p + 3);
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

int	load_sprite(t_texture *text, int x, int y)
{
	mlx_texture_t	*png_image;

	png_image = mlx_load_png(text->file);
	if (!png_image)
		return (0);
	text->height = png_image->height;
	text->width2 = png_image->width;
	text->img = (unsigned int **)malloc(text->height * sizeof(unsigned int *));
	y = -1;
	while (++y < text->height)
	{
		text->img[y] = malloc(text->width2 * sizeof(unsigned int));
		if (!text->img[y])
		{
			free_sprite(text);
			mlx_delete_texture(png_image);
			return (1);
		}
		x = -1;
		while (++x < text->width2)
			text->img[y][x] = get_color(&png_image->pixels[(y * png_image->width
						+ x) * png_image->bytes_per_pixel]);
	}
	mlx_delete_texture(png_image);
	return (1);
}

char	*read_the_file(char *file_name)
{
	int		fd;
	int		bytes;
	char	*line;
	char	buff[2];

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	buff[1] = '\0';
	line = ft_strdup("");
	while (1)
	{
		bytes = read(fd, buff, 1);
		if (bytes == -1)
			return (close(fd), free(line), NULL);
		if (bytes == 0)
			return (close(fd), line);
		line = mod_join(line, buff);
	}
}

int	parsing(t_game *game, char *file)
{
	int	l;

	init_data(game);
	l = ft_strlen(file);
	if (l < 4)
		return (0);
	if (mod_strcomp(".cub", &file[l - 4]))
		return (0);
	if (!get_file_data(game, file))
		return (0);
	if (!valid_map(game))
		return (0);
	if (!get_player_data(game))
		return (0);
	if (!get_sprites(game))
		return (0);
	return (1);
}
