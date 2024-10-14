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
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <float.h>

#define WINDOW_WIDTH   (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT  (MAP_NUM_ROWS * TILE_SIZE)
#define TILE_SIZE 64
#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15
#define MINIMAP_SCALE_FACTOR 1.0
#define NUM_RAYS WINDOW_WIDTH
#define PI 3.14159265
#define TWO_PI (2 * PI)
#define FOV (60 * (PI / 180))
#define FRAME_TIME_LENGTH (1000 / 60) // 60 frames per second

typedef struct s_player
{
    float x;
    float y;
    float width;
    float height;
    int turnDirection; // -1 for left, +1 for right
    int walkDirection; // -1 for back, +1 for front
    float rotationAngle;
    float walkSpeed;
    float turnSpeed;
} t_player;

typedef struct s_ray
{
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float distance;
    int wasHitVertical;
    int isRayFacingUp;
    int isRayFacingDown;
    int isRayFacingLeft;
    int isRayFacingRight;
    int wallHitContent;
} t_ray;

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
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

mlx_t* mlx;
mlx_image_t* img;

t_player player;
t_ray ray[NUM_RAYS];

uint32_t ticksLastFrame = 0;

void draw_rectangle(mlx_image_t* img, int x, int y, int width, int height, uint32_t color)
{
    for (int i = x; i < x + width; i++)
    {
        for (int j = y; j < y + height; j++)
        {
            if (i >= 0 && i < (int)img->width && j >= 0 && j < (int)img->height)
                mlx_put_pixel(img, i, j, color);
        }
    }
}

void draw_line(mlx_image_t* img, int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    int err = dx + dy;

    while (1)
    {
        if (x0 >= 0 && x0 < (int)img->width && y0 >= 0 && y0 < (int)img->height)
            mlx_put_pixel(img, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

int mapHasWallAt(float x, float y)
{
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
        return 1;
    }
    int mapGridIndexX = floor(x / TILE_SIZE);
    int mapGridIndexY = floor(y / TILE_SIZE);
    return map[mapGridIndexY][mapGridIndexX] != 0;
}

void movePlayer(float deltaTime)
{
    player.rotationAngle += player.turnDirection * player.turnSpeed * deltaTime;
    player.rotationAngle = fmod(player.rotationAngle, TWO_PI);
    if (player.rotationAngle < 0)
        player.rotationAngle += TWO_PI;

    float moveStep = player.walkDirection * player.walkSpeed * deltaTime;

    float newPlayerX = player.x + cos(player.rotationAngle) * moveStep;
    float newPlayerY = player.y + sin(player.rotationAngle) * moveStep;
    if (!mapHasWallAt(newPlayerX, newPlayerY)) {
        player.x = newPlayerX;
        player.y = newPlayerY;
    }
}

float normalizeAngle(float angle)
{
    angle = remainder(angle, TWO_PI);
    if(angle < 0)
    {
        angle = TWO_PI + angle;
    }
    return angle;
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1 ) * (y2 - y1));
}

void castRay(float rayAngle, int stripid)
{
    rayAngle = normalizeAngle(rayAngle);

    int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;
    float xstep;
    float ystep;
    float xintercept;
    float yintercept;

    int foundHorzWallhit = 0;
    float horWallHitX = 0;
    float horWallHitY = 0;
    int horWallContent = 0;

    yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDown ? TILE_SIZE : 0;

    xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

    ystep = TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(rayAngle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    while(nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH &&  nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT)
    {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

        if(mapHasWallAt(xToCheck, yToCheck))
        {
            horWallHitX = nextHorzTouchX;
            horWallHitY = nextHorzTouchY;
            horWallContent = map[(int)floor(yToCheck / TILE_SIZE)] [(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallhit = 1;
            break;
        }
        else
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }

    int foundVerWallhit = 0;
    float verWallHitX = 0;
    float verWallHitY = 0;
    int verWallContent = 0;

    xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    yintercept = player.y + (xintercept - player.x) * tan(rayAngle);

    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(rayAngle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVerTouchX = xintercept;
    float nextVerTouchY = yintercept;

    while(nextVerTouchX >= 0 && nextVerTouchX <= WINDOW_WIDTH &&  nextVerTouchY >= 0 && nextVerTouchY <= WINDOW_HEIGHT)
    {
        float xToCheck = nextVerTouchX + (isRayFacingLeft ? -1: 0);
        float yToCheck = nextVerTouchY;

        if(mapHasWallAt(xToCheck, yToCheck))
        {
            verWallHitX = nextVerTouchX;
            verWallHitY = nextVerTouchY;
            verWallContent = map[(int)floor(yToCheck / TILE_SIZE)] [(int)floor(xToCheck / TILE_SIZE)];
            foundVerWallhit  = 1;
            break;
        }
        else
        {
            nextVerTouchX += xstep;
            nextVerTouchY += ystep;
        }
    }

    float horHitDistance =  (foundHorzWallhit)
    ? distanceBetweenPoints(player.x, player.y, horWallHitX, horWallHitY)
    : FLT_MAX;
    float verHitDistance = (foundVerWallhit)
        ? distanceBetweenPoints(player.x, player.y, verWallHitX, verWallHitY)
        : FLT_MAX;
    if (verHitDistance < horHitDistance)
    {
        ray[stripid].distance = verHitDistance;
        ray[stripid].wallHitX = verWallHitX;
        ray[stripid].wallHitY = verWallHitY;
        ray[stripid].wallHitContent = verWallContent;
        ray[stripid].wasHitVertical = 1;
    }
    else
    {
        ray[stripid].distance = horHitDistance;
        ray[stripid].wallHitX = horWallHitX;
        ray[stripid].wallHitY = horWallHitY;
        ray[stripid].wallHitContent = horWallContent;
        ray[stripid].wasHitVertical = 0;
    }
    ray[stripid].rayAngle = rayAngle;
    ray[stripid].isRayFacingDown = isRayFacingDown;
    ray[stripid].isRayFacingUp = isRayFacingUp;
    ray[stripid].isRayFacingLeft = isRayFacingLeft;
    ray[stripid].isRayFacingRight = isRayFacingRight;
}

void castAllRays()
{
    float rayAngle = player.rotationAngle - (FOV / 2);
    for (int stripid = 0; stripid < NUM_RAYS; stripid++)
    {
        castRay(rayAngle, stripid);
        rayAngle += FOV / NUM_RAYS;
    }
}

void renderMap()
{
    for (int i = 0; i < MAP_NUM_ROWS; i++) {
        for (int j = 0; j < MAP_NUM_COLS; j++) {
            int tileX = j * TILE_SIZE;
            int tileY = i * TILE_SIZE;
            uint32_t tileColor = map[i][j] != 0 ? 0x000000FF : 0xE9E9E9FF; // ARGB format
            draw_rectangle(img,
                tileX * MINIMAP_SCALE_FACTOR,
                tileY * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                tileColor);
        }
    }
}

void renderPlayer()
{
    unsigned int playerColor = 0xFA0000FF; // ARGB format
    draw_rectangle(img,
        player.x * MINIMAP_SCALE_FACTOR,
        player.y * MINIMAP_SCALE_FACTOR,
        player.width * MINIMAP_SCALE_FACTOR,
        player.height * MINIMAP_SCALE_FACTOR,
        playerColor);
    // Draw line indicating direction
    draw_line(
        img,
        player.x * MINIMAP_SCALE_FACTOR,
        player.y * MINIMAP_SCALE_FACTOR,
        (player.x + cos(player.rotationAngle) * 40) * MINIMAP_SCALE_FACTOR,
        (player.y + sin(player.rotationAngle) * 40) * MINIMAP_SCALE_FACTOR,
        playerColor);
}

void renderRays()
{
    uint32_t rayColor = 0x38FF00FF; // ARGB format
    for(int i = 0; i < NUM_RAYS; i++)
    {
        draw_line(
            img,
            player.x * MINIMAP_SCALE_FACTOR,
            player.y * MINIMAP_SCALE_FACTOR,
            ray[i].wallHitX * MINIMAP_SCALE_FACTOR,
            ray[i].wallHitY * MINIMAP_SCALE_FACTOR,
            rayColor);
    }
}

void key_hook(mlx_key_data_t keydata, void* param)
{
    (void)param; // Unused parameter
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        mlx_close_window(mlx);
    }
    if (keydata.key == MLX_KEY_UP)
    {
        if (keydata.action == MLX_PRESS)
            player.walkDirection = +1;
        else if (keydata.action == MLX_RELEASE)
            player.walkDirection = 0;
    }
    if (keydata.key == MLX_KEY_DOWN)
    {
        if (keydata.action == MLX_PRESS)
            player.walkDirection = -1;
        else if (keydata.action == MLX_RELEASE)
            player.walkDirection = 0;
    }
    if (keydata.key == MLX_KEY_RIGHT)
    {
        if (keydata.action == MLX_PRESS)
            player.turnDirection = +1;
        else if (keydata.action == MLX_RELEASE)
            player.turnDirection = 0;
    }
    if (keydata.key == MLX_KEY_LEFT)
    {
        if (keydata.action == MLX_PRESS)
            player.turnDirection = -1;
        else if (keydata.action == MLX_RELEASE)
            player.turnDirection = 0;
    }
}

void update(void* param)
{
    (void)param; // Unused parameter

    // Calculate deltaTime
    unsigned int timeNow = mlx_get_time() * 1000;
    float deltaTime = (timeNow - ticksLastFrame) / 1000.0f;
    ticksLastFrame = timeNow;

    movePlayer(deltaTime);
    castAllRays();

    // Clear the image buffer
    memset(img->pixels, 255, img->width * img->height * sizeof(unsigned int));

    // Render functions
    renderMap();
    renderRays();
    renderPlayer();
}

void setup()
{
    mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Raycaster", true);
    if (!mlx)
    {
        fprintf(stderr, "Error initializing MLX.\n");
        exit(EXIT_FAILURE);
    }
    img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img)
    {
        fprintf(stderr, "Error creating image.\n");
        exit(EXIT_FAILURE);
    }
    mlx_image_to_window(mlx, img, 0, 0);

    // Initialize player
    player.x = WINDOW_WIDTH / 2;
    player.y = WINDOW_HEIGHT / 2;

    player.width = 1;
    player.height = 1;
    player.turnDirection = 0;
    player.walkDirection = 0;
    player.rotationAngle = PI / 2;
    player.walkSpeed = 150;
    player.turnSpeed = 45 * (PI / 180);

    // Set up hooks
    mlx_key_hook(mlx, &key_hook, NULL);
    mlx_loop_hook(mlx, &update, NULL);
}

void destroyWindow()
{
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
}

int main()
{
    setup();

    mlx_loop(mlx);

    destroyWindow();

    return 0;
}
