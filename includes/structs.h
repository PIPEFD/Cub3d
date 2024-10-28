/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:42:24 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/28 10:56:06 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "defs.h"
# include "libs.h"

typedef struct s_texture
{
	char				*file;
	int					width2;
	int					height;
	unsigned int		**img;
}						t_texture;

typedef struct s_data
{
	char				**map;

	int					px;
	int					py;
	int					dir;

	t_texture			*no;
	t_texture			*so;
	t_texture			*we;
	t_texture			*ea;

	unsigned int		floor;
	unsigned int		ceiling;

}						t_data;

typedef struct s_render_params
{
	float				perp_distance;
	float				distance_proj_plane;
	float				wall_strip_height;
	int					wall_top_pixel;
	int					wall_bottom_pixel;
	unsigned int		wall_color;
}						t_render_params;

typedef struct s_rectangle_params
{
	int					x;
	int					y;
	int					width;
	int					height;
	unsigned int		color;
}						t_rectangle_params;

typedef struct s_line_params
{
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	unsigned int		color;
}						t_line_params;

typedef struct s_bresenham_vars
{
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	int					dx;
	int					dy;
	int					sx;
	int					sy;
	int					err;
	int					e2;
}						t_bresenham_vars;
typedef struct s_line_draw_params
{
	mlx_image_t			*img;
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	unsigned int		color;
}						t_line_draw_params;

typedef struct s_draw_figures
{
	t_rectangle_params	*rect_params;
	t_line_params		*line_params;
	t_line_draw_params	*line_draw;

}						t_draw_figures;

typedef struct s_ray_cast
{
	int					israyfacingdown;
	int					israyfacingup;
	int					israyfacingright;
	int					israyfacingleft;

	float				xintercept;
	float				yintercept;
	float				xstep;
	float				ystep;

	int					foundhorzwallhit;
	float				horwallhitx;
	float				horwallhity;
	int					horwallcontent;

	int					foundverwallhit;
	float				verwallhitx;
	float				verwallhity;
	int					verwallcontent;

	float				nexthorztouchx;
	float				nexthorztouchy;
	float				nextvertouchx;
	float				nextvertouchy;

	float				horhitdistance;
	float				verhitdistance;
}						t_ray_cast;
typedef struct s_player
{
	float				x;
	float				y;
	char				dir;
	int					mousedirection;
	int					turndirection;
	int					walkdirection;
	int					strafedirection;
	float				rotationangle;
	float				walkspeed;
	float				turnspeed;
}						t_player;

typedef struct s_ray
{
	float				rayangle;
	float				wallhitx;
	float				wallhity;
	float				distance;
	int					washitvertical;
	int					israyfacingup;
	int					israyfacingdown;
	int					israyfacingleft;
	int					israyfacingright;
	int					wallhitcontent;
}						t_ray;

typedef struct s_game
{
	unsigned int		strip[WINDOW_HEIGHT];

	t_texture			*no;
	t_texture			*so;
	t_texture			*we;
	t_texture			*ea;
	unsigned int		floor;
	unsigned int		ceiling;

	mlx_t				*mlx;
	mlx_image_t			*img;
	t_player			player;
	t_render_params		render_params;
	t_draw_figures		draw_figures;
	t_ray_cast			ray_casts[NUM_RAYS];
	t_ray				rays[NUM_RAYS];
	unsigned int		tickslastframe;
	char				**map;
	size_t				heigth;
	size_t				width;

}						t_game;

#endif