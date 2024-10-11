/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipe <pipe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 00:32:57 by pipe              #+#    #+#             */
/*   Updated: 2024/10/11 00:33:56 by pipe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -----------------------------------------------------------------------------
#include "../mlx/include/MLX42/MLX42.h"
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <float.h>

#define TILE_SIZE 64
#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15
#define WINDOW_WIDTH   (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT  (MAP_NUM_ROWS * TILE_SIZE)
#define MINIMAP_SCALE_FACTOR 0.2
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

typedef struct s_game
{
    mlx_t* mlx;
    mlx_image_t* img;
    t_player player;
    t_ray rays[NUM_RAYS];
    char** map;
    uint32_t ticksLastFrame;
} t_game;

// Declaración de funciones
void setup(t_game* game);
void destroyWindow(t_game* game);
void draw_rectangle(mlx_image_t* img, int x, int y, int width, int height, uint32_t color);
void draw_line(mlx_image_t* img, int x0, int y0, int x1, int y1, uint32_t color);
int mapHasWallAt(t_game* game, float x, float y);
void movePlayer(t_game* game, float deltaTime);
float normalizeAngle(float angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
void castRay(t_game* game, float rayAngle, int stripid);
void castAllRays(t_game* game);
void renderMap(t_game* game);
void renderPlayer(t_game* game);
void renderRays(t_game* game);
void render3DProjection(t_game* game);
void key_hook(mlx_key_data_t keydata, void* param);
void update(void* param);

int main()
{
    t_game game;
    setup(&game);

    mlx_loop(game.mlx);

    destroyWindow(&game);

    return 0;
}

void setup(t_game* game)
{
    game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Raycaster", true);
    if (!game->mlx)
    {
        fprintf(stderr, "Error initializing MLX.\n");
        exit(EXIT_FAILURE);
    }
    game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!game->img)
    {
        fprintf(stderr, "Error creating image.\n");
        exit(EXIT_FAILURE);
    }
    mlx_image_to_window(game->mlx, game->img, 0, 0);

    // Inicializar jugador
    game->player.x = WINDOW_WIDTH / 2;
    game->player.y = WINDOW_HEIGHT / 2;

    game->player.width = 1;
    game->player.height = 1;
    game->player.turnDirection = 0;
    game->player.walkDirection = 0;
    game->player.rotationAngle = PI / 2;
    game->player.walkSpeed = 150;
    game->player.turnSpeed = 45 * (PI / 180);

    game->ticksLastFrame = 0;

    // Inicializar mapa
    const char* mapData[MAP_NUM_ROWS] = {
        "111111111111111",
        "100000000000101",
        "100100000000101",
        "101110000010101",
        "100000000010101",
        "100000001111101",
        "100000000000001",
        "100000000000001",
        "111111000111101",
        "100000000000001",
        "111111111111111"
    };

    game->map = malloc(sizeof(char*) * MAP_NUM_ROWS);
    if (!game->map)
    {
        fprintf(stderr, "Error allocating memory for map.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAP_NUM_ROWS; i++)
    {
        game->map[i] = strdup(mapData[i]);
        if (!game->map[i])
        {
            fprintf(stderr, "Error duplicating map row.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Configurar hooks
    mlx_key_hook(game->mlx, &key_hook, game);
    mlx_loop_hook(game->mlx, &update, game);
}

void destroyWindow(t_game* game)
{
    if (game->img)
    {
        mlx_delete_image(game->mlx, game->img);
        game->img = NULL;
    }
    if (game->mlx)
    {
        mlx_terminate(game->mlx);
        game->mlx = NULL;
    }
    // Liberar memoria del mapa
    if (game->map)
    {
        for (int i = 0; i < MAP_NUM_ROWS; i++)
        {
            free(game->map[i]);
        }
        free(game->map);
        game->map = NULL;
    }
}

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

int mapHasWallAt(t_game* game, float x, float y)
{
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
        return 1;
    }
    int mapGridIndexX = floor(x / TILE_SIZE);
    int mapGridIndexY = floor(y / TILE_SIZE);
    if (mapGridIndexY < 0 || mapGridIndexY >= MAP_NUM_ROWS || mapGridIndexX < 0 || mapGridIndexX >= MAP_NUM_COLS)
        return 1;
    char tile = game->map[mapGridIndexY][mapGridIndexX];
    return tile != '0';
}

void movePlayer(t_game* game, float deltaTime)
{
    t_player* player = &game->player;

    player->rotationAngle += player->turnDirection * player->turnSpeed * deltaTime;
    player->rotationAngle = fmod(player->rotationAngle, TWO_PI);
    if (player->rotationAngle < 0)
        player->rotationAngle += TWO_PI;

    float moveStep = player->walkDirection * player->walkSpeed * deltaTime;

    float newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
    float newPlayerY = player->y + sin(player->rotationAngle) * moveStep;
    if (!mapHasWallAt(game, newPlayerX, newPlayerY)) {
        player->x = newPlayerX;
        player->y = newPlayerY;
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

void castRay(t_game* game, float rayAngle, int stripid)
{
    rayAngle = normalizeAngle(rayAngle);

    t_player* player = &game->player;
    t_ray* rays = game->rays;

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

    yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDown ? TILE_SIZE : 0;

    xintercept = player->x + (yintercept - player->y) / tan(rayAngle);

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

        if(mapHasWallAt(game, xToCheck, yToCheck))
        {
            horWallHitX = nextHorzTouchX;
            horWallHitY = nextHorzTouchY;
            horWallContent = game->map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
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

    xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    yintercept = player->y + (xintercept - player->x) * tan(rayAngle);

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

        if(mapHasWallAt(game, xToCheck, yToCheck))
        {
            verWallHitX = nextVerTouchX;
            verWallHitY = nextVerTouchY;
            verWallContent = game->map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
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
        ? distanceBetweenPoints(player->x, player->y, horWallHitX, horWallHitY)
        : FLT_MAX;
    float verHitDistance = (foundVerWallhit)
        ? distanceBetweenPoints(player->x, player->y, verWallHitX, verWallHitY)
        : FLT_MAX;
    if (verHitDistance < horHitDistance)
    {
        rays[stripid].distance = verHitDistance;
        rays[stripid].wallHitX = verWallHitX;
        rays[stripid].wallHitY = verWallHitY;
        rays[stripid].wallHitContent = verWallContent;
        rays[stripid].wasHitVertical = 1;
    }
    else
    {
        rays[stripid].distance = horHitDistance;
        rays[stripid].wallHitX = horWallHitX;
        rays[stripid].wallHitY = horWallHitY;
        rays[stripid].wallHitContent = horWallContent;
        rays[stripid].wasHitVertical = 0;
    }
    rays[stripid].rayAngle = rayAngle;
    rays[stripid].isRayFacingDown = isRayFacingDown;
    rays[stripid].isRayFacingUp = isRayFacingUp;
    rays[stripid].isRayFacingLeft = isRayFacingLeft;
    rays[stripid].isRayFacingRight = isRayFacingRight;
}

void castAllRays(t_game* game)
{
    float rayAngle = game->player.rotationAngle - (FOV / 2);
    for (int stripid = 0; stripid < NUM_RAYS; stripid++)
    {
        castRay(game, rayAngle, stripid);
        rayAngle += FOV / NUM_RAYS;
    }
}

void renderMap(t_game* game)
{
    for (int i = 0; i < MAP_NUM_ROWS; i++) {
        for (int j = 0; j < MAP_NUM_COLS; j++) {
            int tileX = j * TILE_SIZE;
            int tileY = i * TILE_SIZE;
            uint32_t tileColor = game->map[i][j] != '0' ? 0x000000FF : 0xE9E9E9FF; // ARGB format
            draw_rectangle(game->img,
                tileX * MINIMAP_SCALE_FACTOR,
                tileY * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                tileColor);
        }
    }
}

void renderPlayer(t_game* game)
{
    unsigned int playerColor = 0xFA0000FF; // ARGB format
    draw_rectangle(game->img,
        game->player.x * MINIMAP_SCALE_FACTOR,
        game->player.y * MINIMAP_SCALE_FACTOR,
        game->player.width * MINIMAP_SCALE_FACTOR,
        game->player.height * MINIMAP_SCALE_FACTOR,
        playerColor);
    // Dibujar línea indicando la dirección
    draw_line(
        game->img,
        game->player.x * MINIMAP_SCALE_FACTOR,
        game->player.y * MINIMAP_SCALE_FACTOR,
        (game->player.x + cos(game->player.rotationAngle) * 40) * MINIMAP_SCALE_FACTOR,
        (game->player.y + sin(game->player.rotationAngle) * 40) * MINIMAP_SCALE_FACTOR,
        playerColor);
}

void renderRays(t_game* game)
{
    uint32_t rayColor = 0x38FF00FF; // ARGB format
    for(int i = 0; i < NUM_RAYS; i += 50) // Reducir el número de rayos dibujados en el minimapa para mayor claridad
    {
        draw_line(
            game->img,
            game->player.x * MINIMAP_SCALE_FACTOR,
            game->player.y * MINIMAP_SCALE_FACTOR,
            game->rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
            game->rays[i].wallHitY * MINIMAP_SCALE_FACTOR,
            rayColor);
    }
}

void render3DProjection(t_game* game)
{
    for (int i = 0; i < NUM_RAYS; i++)
    {
        // Corregir la distancia por el efecto fish-eye
        float perpDistance = game->rays[i].distance * cos(game->rays[i].rayAngle - game->player.rotationAngle);
        // Calcular la distancia al plano de proyección
        float distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
        // Calcular la altura proyectada de la pared
        float wallStripHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

        // Calcular la parte superior e inferior de la pared
        int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

        // Dibujar la pared
        uint32_t wallColor;
        if (game->rays[i].wasHitVertical)
            wallColor = 0xFFFFFFFF; // Color blanco para paredes verticales
        else
            wallColor = 0xCCCCCCFF; // Color gris claro para paredes horizontales

        for (int y = wallTopPixel; y < wallBottomPixel; y++)
        {
            mlx_put_pixel(game->img, i, y, wallColor);
        }

        // Dibujar el suelo
        for (int y = wallBottomPixel; y < WINDOW_HEIGHT; y++)
        {
            mlx_put_pixel(game->img, i, y, 0x7F7F7FFF); // Color gris oscuro para el suelo
        }

        // Dibujar el techo
        for (int y = 0; y < wallTopPixel; y++)
        {
            mlx_put_pixel(game->img, i, y, 0x000000FF); // Color negro para el techo
        }
    }
}

void key_hook(mlx_key_data_t keydata, void* param)
{
    t_game* game = (t_game*)param;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        mlx_close_window(game->mlx);
    }
    if (keydata.key == MLX_KEY_UP)
    {
        if (keydata.action == MLX_PRESS)
            game->player.walkDirection = +1;
        else if (keydata.action == MLX_RELEASE)
            game->player.walkDirection = 0;
    }
    if (keydata.key == MLX_KEY_DOWN)
    {
        if (keydata.action == MLX_PRESS)
            game->player.walkDirection = -1;
        else if (keydata.action == MLX_RELEASE)
            game->player.walkDirection = 0;
    }
    if (keydata.key == MLX_KEY_RIGHT)
    {
        if (keydata.action == MLX_PRESS)
            game->player.turnDirection = +1;
        else if (keydata.action == MLX_RELEASE)
            game->player.turnDirection = 0;
    }
    if (keydata.key == MLX_KEY_LEFT)
    {
        if (keydata.action == MLX_PRESS)
            game->player.turnDirection = -1;
        else if (keydata.action == MLX_RELEASE)
            game->player.turnDirection = 0;
    }
}

void update(void* param)
{
    t_game* game = (t_game*)param;

    // Calcular deltaTime
    unsigned int timeNow = mlx_get_time() * 1000;
    float deltaTime = (timeNow - game->ticksLastFrame) / 1000.0f;
    game->ticksLastFrame = timeNow;

    movePlayer(game, deltaTime);
    castAllRays(game);

    // Limpiar el buffer de imagen
    memset(game->img->pixels, 0, game->img->width * game->img->height * sizeof(unsigned int));

    // Funciones de renderizado
    // render3DProjection(game);
    renderMap(game);
    renderRays(game);
    renderPlayer(game);
}
