/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:42:24 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/25 11:24:50 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libs.h"
# include "defs.h"

typedef struct s_texture {
	char			*file;				// Filename
	int				width;				// Width
	int				height;				// Height
	unsigned int	**img;				// Array with the texture
} t_texture;

typedef struct s_data
{
	char			**map;		// The map 

	int				px;			// Player x
	int				py;			// Player y
	int				dir;		// Player direction

	t_texture		*no;		// North image data-struct
	t_texture		*so;		// South image data-struct
	t_texture		*we;		// West image data-struct
	t_texture		*ea;		// East image data-struct

	unsigned int	floor;		// Floor RGB
	unsigned int	ceiling;	// Ceiling RGB

}	t_data;


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

typedef struct s_bresenham_vars {
    int x0;
    int y0;
    int x1;
    int y1;
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;
} t_bresenham_vars;
typedef struct s_line_draw_params {
    mlx_image_t *img;
    int x0;
    int y0;
    int x1;
    int y1;
    unsigned int color;
} t_line_draw_params;

typedef struct s_draw_figures
{
	t_rectangle_params	*rect_params;
	t_line_params		*line_params;
	t_line_draw_params	*line_draw;
	// Puedes agregar más tipos de figuras en el futuro
}						t_draw_figures;

typedef struct s_ray_cast
{
	// Direcciones del rayo
	int					isRayFacingDown;
	int					isRayFacingUp;
	int					isRayFacingRight;
	int					isRayFacingLeft;

	// Interceptos y pasos
	float				xintercept;
	float				yintercept;
	float				xstep;
	float				ystep;

	// Información de impacto horizontal
	int					foundHorzWallhit;
	float				horWallHitX;
	float				horWallHitY;
	int					horWallContent;

	// Información de impacto vertical
	int					foundVerWallhit;
	float				verWallHitX;
	float				verWallHitY;
	int					verWallContent;

	// Próximos puntos de intersección
	float				nextHorzTouchX;
	float				nextHorzTouchY;
	float				nextVerTouchX;
	float				nextVerTouchY;

	// Distancias
	float				horHitDistance;
	float				verHitDistance;
}						t_ray_cast;
typedef struct s_player
{
	float				x;
	float				y;
	float				width;
	float				height;
	char				dir;
	int 				turnDirection;   // -1 for left, +1 for right
	int 				walkDirection;   // -1 for back, +1 for front
	int 				strafeDirection; // -1 para izquierda, +1 para derecha
	float				rotationAngle;
	float				walkSpeed;
	float				turnSpeed;
}						t_player;

typedef struct s_ray
{
	float				rayAngle;
	float				wallHitX;	//Ray collision X
	float				wallHitY;	//Ray collision Y
	float				distance;
	int					wasHitVertical;
	int					isRayFacingUp;
	int					isRayFacingDown;
	int					isRayFacingLeft;
	int					isRayFacingRight;
	int					wallHitContent;
}						t_ray;

/*
typedef struct s_data
{
	char			**map;		// The map 

	int				px;			// Player x
	int				py;			// Player y
	int				dir;		// Player direction

	t_texture		*no;		// North image data-struct
	t_texture		*so;		// South image data-struct
	t_texture		*we;		// West image data-struct
	t_texture		*ea;		// East image data-struct

	unsigned int	floor;		// Floor RGB
	unsigned int	ceiling;	// Ceiling RGB

}	t_data;
*/

typedef struct s_game
{
	unsigned int	strip[WINDOW_HEIGHT];
	t_texture		*no;		// North image data-struct
	t_texture		*so;		// South image data-struct
	t_texture		*we;		// West image data-struct
	t_texture		*ea;

	unsigned int	floor;		// Floor RGB
	unsigned int	ceiling;	// Ceiling RGB
	
	mlx_t				*mlx;
	mlx_image_t			*img;
	t_player			player;
	t_render_params		render_params;
	t_draw_figures		draw_figures;
	t_ray_cast			ray_casts[NUM_RAYS];
	t_ray				rays[NUM_RAYS];
	unsigned int		ticksLastFrame;
	char				**map;
	size_t				heigth;
	size_t				width;

}						t_game;

#endif //STRUCTS_H