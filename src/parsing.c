/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:34:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/21 11:58:25 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_player_data(t_game *data)
{
	int	y;
	int	x;

	y = -1;
	while(data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (ft_strchr("NSWE", data->map[y][x]))
			{
				if (data->player.dir != 0)
					return (0);
				data->player.x = x * TILE_SIZE;
				data->player.y = y * TILE_SIZE;
				data->player.dir = data->map[y][x];
			}
		}
	}
	return (data->player.dir);
}

int	flood_fill(char **map, int x, int y)
{
	int	end;

	if (!map[y] || !map[y][x] || map[y][x] == ' ')
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

int	everything_closed(char **map)
{
	int		y;
	int		x;
	char	**temp_map;

	y = -1;
	temp_map = split_cpy(map);
	y = -1;
	while(temp_map[++y])
	{
		x = -1;
		while (temp_map[y][++x])
			if (ft_strchr("0NSWE", map[y][x]) && flood_fill(temp_map, x, y))
				return (split_free(temp_map),  0);
	}
	return (split_free(temp_map), 1);
}

int	non_valid_characters(char **map)
{
	int	y;
	int	x;

	y = -1;
	while(map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (!ft_strchr("01 NSWE", map[y][x]))
				return (1);
	}
	return (0);
}

int	valid_map(char **map)
{
	if (non_valid_characters(map))
		return (0);
	if (!everything_closed(map))
		return (0);
	return (1);
}

int	get_map(t_game *data, char **file)
{
	int	y;
	int	x;

	y = split_len(file);
	while (--y >= 0)
	{
		x = 0;
		while (file[y][x] && ft_strchr("01 NSWE", file[y][x]))
			x ++;
		if (!ft_strchr("01 NSWE", file[y][x]))
			break ;
	}
	data->map = split_cpy(&file[y + 1]);
	return (!(!data->map));
}

/*
	if (!isnum(red_green_blue[0]) || \
		!isnum(red_green_blue[1]) || \
		!isnum(red_green_blue[2]))
		return (0);
*/

int	get_rgb(char *line)
{
	unsigned char	rgb[3];
	char			**red_green_blue;

	red_green_blue = ft_split(line, ',');
	if (split_len(red_green_blue) != 3)
		return (0);
	rgb[0] = (unsigned char)ft_atoi(red_green_blue[0]);
	rgb[1] = (unsigned char)ft_atoi(red_green_blue[1]);
	rgb[2] = (unsigned char)ft_atoi(red_green_blue[2]);
	return (0 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

/*
		if ((data->no->file && !ft_strcmp(file[i], "NO ")) || \
			(data->so->file && !ft_strcmp(file[i], "SO ")) || \
			(data->we->file && !ft_strcmp(file[i], "WE ")) || \
			(data->ea->file && !ft_strcmp(file[i], "EA ")) || \
			(data->floor == 0 && !ft_strcmp(file[i], "F ")) || \
			(data->ceiling == 0 && !ft_strcmp(file[i], "C ")))
			return (0);
*/

int	mod_strcomp(char *s1, char *s2)
{
	int	i;
	
	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (1);
	return (0);
}

char	*get_filename(char **file, char *id)
{
	int	i;
	
	i = -1;
	while (file[++i])
	{
		if (!mod_strcomp(file[i], id))
			return (ft_strdup(&file[i][3]));
	}
	return (NULL);
}

void	load_sprite(void *mlx, t_texture *text)
{
	xpm_t			*xpm_image;
	mlx_image_t		*mlx_img;
	int				x;
	int				y;

	xpm_image = mlx_load_xpm42(text->file);
	if (!xpm_image)
    	return;
	mlx_img = mlx_texture_to_image(mlx, &xpm_image->texture);
	text->height = mlx_img->height;
	text->width = mlx_img->width;
	text->img = (int **)malloc(text->height * sizeof(int *));
	y = -1;
	while (++y < text->height)
	{
		text->img[y] = malloc(text->width * sizeof(int));
		x = -1;
		while (++x < text->width)
			text->img[y][x] = ((unsigned int *)mlx_img->pixels)[y * mlx_img->width + x];
	}
}

int	get_sprites(t_game *data)
{
	load_sprite(data->mlx, data->no);
	load_sprite(data->mlx, data->so);
	load_sprite(data->mlx, data->we);
	load_sprite(data->mlx, data->ea);
	return (1);
}

char	*mod_join(char *s1, char *s2)
{
	char	*str;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char ) * size);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, size);
	free(s1);
	return (str);
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

int	get_file_data(t_game *data, char *file_name)
{
	char *the_whole_file;
	char **file;

	the_whole_file = read_the_file(file_name);
	file = ft_split(the_whole_file, '\n');
	free(the_whole_file);
	data->no->file = get_filename(file, "NO ");
	data->so->file = get_filename(file, "SO ");
	data->we->file = get_filename(file, "WE ");
	data->ea->file = get_filename(file, "EA ");
	if (!get_map(data, file))
		return (split_free(file), 0);
	split_free(file);
	if (!get_sprites(data))
		return (0);
	return (1);
}

void	init_data(t_game *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", true);
	if (!data->mlx)
		return ((void)printf("Error initializing MLX.\n"));
	data->player.dir = 0;
	data->no = (t_texture *)malloc(sizeof(t_texture));
	data->so = (t_texture *)malloc(sizeof(t_texture));
	data->ea = (t_texture *)malloc(sizeof(t_texture));
	data->we = (t_texture *)malloc(sizeof(t_texture));
	data->ceiling = 0;
	data->floor = 0;
	data->map = NULL;
}

void get_map_data(t_game *game)
{
	int	i;

	i = -1;
	game->width = 0;
	while (game->map[++i])
		if (game->width < ft_strlen(game->map[i]) * TILE_SIZE)
			game->width = ft_strlen(game->map[i]) * TILE_SIZE;
	game->heigth = split_len(game->map) * TILE_SIZE;
}

int parsing(t_game *game, char *file_name)
{
	init_data(game);
	if (!get_file_data(game, file_name))
		return(0);
	if (!valid_map(game->map))
		return (0);
	get_map_data(game);
	if (!get_player_data(game))
		return (0);
	return (1);
}
