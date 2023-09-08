#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include "../inc/header.h"
#include "../inc/const.h"
#include "../inc/texture.h"

/**
 * playerCharacter - sets characteristics of the player
 * Return: Nothing
 */
void setupPlayer(SDL_Instance instance)
{
    p.x = WINDOW_WIDTH / 2;
    p.y = WINDOW_HEIGHT / 2;
    p.width = 10;
    p.height = 10;
    p.turnDirection = 0;
    p.walkDirection = 0;
    p.rotationAngle = PI / 2;
    p.walkSpeed = 100;
    p.turnSpeed = 45 * (PI / 180);
    /* Allocates the total amount of bytes in the memory to hold colorbuffer */
    colorBuffer = (Uint32*) malloc(sizeof(Uint32) * (Uint32)WINDOW_WIDTH * (Uint32)WINDOW_HEIGHT);
    /* Creating the SDL_Texture to display the colorbuffer */
    colorBufferTexture = SDL_CreateTexture(
        instance.renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    );

    /* loades textures from the textures.h */
    textures[0] = (Uint32 *) REDBRICK_TEXTURE;
    textures[1] = (Uint32 *) PURPLESTONE_TEXTURE;
}

/**
 * renderPlayer - rendering the player
 * @instance: sdl instance
 * Returns: nothing
 */
void renderPlayer(SDL_Instance instance)
{
    SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255);
    SDL_Rect playerRect = {
        p.x * MINIMAP_SCALE_FACTOR,
        p.y * MINIMAP_SCALE_FACTOR,
        p.width * MINIMAP_SCALE_FACTOR,
        p.height * MINIMAP_SCALE_FACTOR
    };
    SDL_RenderFillRect(instance.renderer, &playerRect);

    SDL_RenderDrawLine(
        instance.renderer,
        MINIMAP_SCALE_FACTOR * p.x,
        MINIMAP_SCALE_FACTOR * p.y,
        MINIMAP_SCALE_FACTOR * (p.x + cos(p.rotationAngle) * 40),
        MINIMAP_SCALE_FACTOR * (p.y + sin(p.rotationAngle) * 40)
    );
}

/**
 * mapHasWallAt - detects walls collisions
 * @x: position x
 * @y: position y
 * Return: 0 if true, 1 if false
 */
int mapHasWallAt(float x, float y)
{
    int mapGridIndexX, mapGridIndexY;

    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
        return (FALSE);
    }
    mapGridIndexX = floor(x / TILE_SIZE);
    mapGridIndexY = floor(y / TILE_SIZE);
    return (map[mapGridIndexY][mapGridIndexX] != 0);
}

/**
 * movesPlayer - moving the player
 * @deltaTime: time
 * Return: nothing
 */
void movesPlayer(float deltaTime)
{
    float moveStep, newPlayerX, newPlayerY;

    //deltaTime = 0.0010;
    p.rotationAngle += p.turnDirection * p.turnSpeed * 1.10 * deltaTime;

    moveStep = p.walkDirection * p.walkSpeed * deltaTime;

    newPlayerX = p.x + cos(p.rotationAngle) * moveStep;
    newPlayerY = p.y + sin(p.rotationAngle) * moveStep;

    if (!mapHasWallAt(newPlayerX, newPlayerY))
    {
        p.x = newPlayerX;
        p.y = newPlayerY;
    }
}