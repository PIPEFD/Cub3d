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
    uint32_t ticksLastFrame;
} t_game;

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
    if (!mapHasWallAt(newPlayerX, newPlayerY)) {
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
            uint32_t tileColor = map[i][j] != 0 ? 0x000000FF : 0xE9E9E9FF; // ARGB format
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
    // Draw line indicating direction
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
    for(int i = 0; i < NUM_RAYS; i += 50) // Reduce the number of rays drawn on the minimap for clarity
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
        // Correct the distance for the fish-eye effect
        float perpDistance = game->rays[i].distance * cos(game->rays[i].rayAngle - game->player.rotationAngle);
        // Calculate the distance to the projection plane
        float distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
        // Calculate projected wall height
        float wallStripHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

        // Calculate top and bottom of the wall
        int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

        // Draw the wall
        uint32_t wallColor;
        if (game->rays[i].wasHitVertical)
            wallColor = 0xFFFFFFFF; // White color for vertical walls
        else
            wallColor = 0xCCCCCCFF; // Light gray color for horizontal walls

        for (int y = wallTopPixel; y < wallBottomPixel; y++)
        {
            mlx_put_pixel(game->img, i, y, wallColor);
        }

        // Draw the floor
        for (int y = wallBottomPixel; y < WINDOW_HEIGHT; y++)
        {
            mlx_put_pixel(game->img, i, y, 0x7F7F7FFF); // Dark gray color for floor
        }

        // Draw the ceiling
        for (int y = 0; y < wallTopPixel; y++)
        {
            mlx_put_pixel(game->img, i, y, 0x000000FF); // Black color for ceiling
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

    // Calculate deltaTime
    unsigned int timeNow = mlx_get_time() * 1000;
    float deltaTime = (timeNow - game->ticksLastFrame) / 1000.0f;
    game->ticksLastFrame = timeNow;

    movePlayer(game, deltaTime);
    castAllRays(game);

    // Clear the image buffer
    memset(game->img->pixels, 0, game->img->width * game->img->height * sizeof(unsigned int));

    // Render functions
    render3DProjection(game);
    renderMap(game);
    renderRays(game);
    renderPlayer(game);
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

    // Initialize player
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

    // Set up hooks
    mlx_key_hook(game->mlx, &key_hook, game);
    mlx_loop_hook(game->mlx, &update, game);
}

void destroyWindow(t_game* game)
{
    mlx_delete_image(game->mlx, game->img);
    mlx_terminate(game->mlx);
}

int main()
{
    t_game game;
    setup(&game);

    mlx_loop(game.mlx);

    destroyWindow(&game);

    return 0;
}
