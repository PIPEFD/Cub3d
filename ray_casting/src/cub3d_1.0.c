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

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "../mlx/include/MLX42/MLX42.h"
#include "../inc/cub3d.h"

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;



typedef struct s_grid
{
	// int			argc;
	// char		**argv;
	// char		*name;
	void		*mlx_connection;
	void		*mlx_window;
	t_img		img;
    int grid[MAP_NUM_ROWS][MAP_NUM_COLS];

	// double		color;
	// double		julia_x;
	// double		julia_y;
	// double		hypo_value;
	// int			interations;
	// t_movement	move;
}				t_grid;

typedef struct {
    float x, y, radius, rotationAngle, moveSpeed, rotationSpeed;
    int turnDirection, walkDirection;
} Player;

typedef struct {
    int grid[MAP_NUM_ROWS][MAP_NUM_COLS];
} Map;

typedef struct {
    float rayAngle, distance;
    int wallHitX, wallHitY;
    bool wasHitVertical;
} Ray;

Map map;
Player player;
Ray rays[NUM_RAYS];

Map map = {{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
}};
    // memcpy(map.grid, tempMap, sizeof(tempMap));


void initPlayer() {
    player.x = WINDOW_WIDTH / 2;
    player.y = WINDOW_HEIGHT / 7;
    player.radius = 4;
    player.rotationAngle = PI / 2;  // Facing up
    player.moveSpeed = 4.0;
    player.rotationSpeed = 3 * (PI / 180);  // 3 degrees per frame
    player.turnDirection = 0;
    player.walkDirection = 0;
}

bool hasWallAt(float x, float y) {
    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return true;
    int mapGridIndexX = floor(x / TILE_SIZE);
    int mapGridIndexY = floor(y / TILE_SIZE);
    return map.grid[mapGridIndexY][mapGridIndexX] != 0;
}

void movePlayer() {
    player.rotationAngle += player.turnDirection * player.rotationSpeed;
    float moveStep = player.walkDirection * player.moveSpeed;
    float newX = player.x + cos(player.rotationAngle) * moveStep;
    float newY = player.y + sin(player.rotationAngle) * moveStep;
    if (!hasWallAt(newX, newY)) {
        player.x = newX;
        player.y = newY;
    }
}



void	fractal_render(t_grid *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			take_pixel(x, y, fractal);
		}
	}
	mlx_clear_window(fractal->mlx_connection, fractal->mlx_window);
	mlx_put_image_to_window(fractal->mlx_connection, 
							fractal->mlx_window, 
							fractal->img.img_ptr, 
							0, 0);
}
void handleKey(int key, int action) {
    if (action == MLX_PRESS || action == MLX_REPEAT) {
        if (key == MLX_KEY_W) player.walkDirection = 1;
        if (key == MLX_KEY_S) player.walkDirection = -1;
        if (key == MLX_KEY_A) player.turnDirection = -1;
        if (key == MLX_KEY_D) player.turnDirection = 1;
    } else if (action == MLX_RELEASE) {
        if (key == MLX_KEY_W || key == MLX_KEY_S) player.walkDirection = 0;
        if (key == MLX_KEY_A || key == MLX_KEY_D) player.turnDirection = 0;
    }
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	if (*s != '\0')
	{
		write(fd, s, 1);
		ft_putstr_fd(s + 1, fd);
	}
}
void	grid_data(t_grid *grid)
{
    int temp_grid[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    for (int i = 0; i < MAP_NUM_ROWS; i++) {
        for (int j = 0; j < MAP_NUM_COLS; j++) {
            grid->grid[i][j] = temp_grid[i][j];
        }
    }
}
	// fractal->hypo_value = 4;
	// fractal->interations = 42;
	// fractal->move.zoom = 0.5;
	// fractal->move.x_ran = 0.0;
	// fractal->move.y_ran = 0.0;


void	malloc_error(void)
{
	ft_putstr_fd(MSG_N, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
void grid_init(t_grid *grid) {
    // Clear image here if needed
    grid->mlx_connection = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Raycasting with MLX42", true);
	if (NULL == grid->mlx_connection)
		malloc_error();
	// grid->mlx_window = mlx_(grid->mlx_connection, 
	// 									WINDOW_WIDTH, 
	// 									WINDOW_HEIGHT, 
	// 									WIN_TITLE);
	grid->img.img_ptr = mlx_new_image(grid->mlx_connection, \
										WINDOW_WIDTH, WINDOW_HEIGHT);
	// grid->img.pixels_ptr = mlx_(grid->img.img_ptr, 
	// 										&grid->img.bpp, 
	// 										&grid->img.line_len, 
	// 										&grid->img.endian);
	grid_data(grid);
	// events_init(grid);
}

    // Draw the player and other game elements

// int main(void) {
//     mlx_t *mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Raycasting with MLX42", true);
//     if (!mlx) return -1;

//     // initMap();
//     // // initPlayer();

//     // mlx_image_t *image = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
//     // // mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
//     // // mlx_key_hook(mlx, handleKey, NULL);
//     // mlx_loop_hook(mlx, (void (*)(void*))renderGame, image);

//     mlx_loop(mlx);
//     mlx_terminate(mlx);
//     return 0;
// }

int setup()
{
	player.x = WINDOW_WIDTH / 2;
	player.y = WINDOW_HEIGHT / 2;

	player.width = 1;
	player.height = 1;
	player.turnDirection = 0;
	player.walkDirection = 0;
	player.rotationAngle = PI / 2;
	player.walkSpeed = 50;
	player.turnSpeed = 45 * (PI / 180);
	// player.fov =   60 * ( PI / 180);
	//TO DO:
	// Initialize and setup game objects
	// // playerX = 0;
	// // playerY = 0;
    return(0);
}

int main(void)
{
	t_game *game;
    
    setup();

    if (!(game = mlx_init(WIDTH, HEIGHT, "CUB3D", true)))
    {
        puts(mlx_strerror(mlx_errno));
        return(EXIT_FAILURE);
    }

    while (game)
	// Gotta error check this stuff
    {  
        if (!(image = mlx_new_image(game, 128, 128)))
        {
            mlx_close_window(mlx);
            puts(mlx_strerror(mlx_errno));
            return(EXIT_FAILURE);
        }
        if (mlx_image_to_window(game, image, 0, 0) == -1)
        {
            mlx_close_window(mlx);
            puts(mlx_strerror(mlx_errno));
            return(EXIT_FAILURE);
        }
    }
    // mlx_hook(game.mlx_win, 17, 1L << 17, , &game);
	// mlx_hook(game.mlx_win, 2, 1L << 0, , &game);
	// mlx_hook(game.mlx_win, 3, 1L << 1, , &game);
	
	// mlx_loop_hook(mlx, ft_randomize, mlx);
	// mlx_loop_hook(mlx, ft_hook, mlx);


	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}