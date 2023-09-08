#include <SDL2/SDL.h>
#include "../inc/header.h"
#include "../inc/const.h"

/**
 * generate3Dview - create 3d projection
 * Return: Nothing
 */
void generate3DProjection(void)
{
    int i, y;
    float perpDistance, distanceProjPlane, projectedWallHeight;
    int wallStripHeight, wallTopPixel, wallBottomPixel;
    int textureOffsetX;
    int distanceFromTop, textureOffsetY;
    Uint32 texelColor;
    (void)texelColor;
    int texNum;

    for (i = 0; i < NUM_RAYS; i++)
    {
        perpDistance = rays[i].distance * cos(rays[i].rayAngle - p.rotationAngle);
        distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
        projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

        wallStripHeight = (int)projectedWallHeight;

        wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

        /* Cieling */
        for (y = 0; y < wallTopPixel; y++)
            colorBuffer[(WINDOW_WIDTH * y) + i] = 0x190B33;

        /* calculating texture offset X */
        if (rays[i].wasHitVertical)
            textureOffsetX = (int)rays[i].wallHitY % TEXTURE_HEIGHT;
        else
            textureOffsetX = (int)rays[i].wallHitX % TEXTURE_WIDTH;

        /* get the correct texture id number from the map */
        texNum = rays[i].wallHitContent - 1;

        /* render the wall from wallTopPixel to wallBottomPixel */
        for (y = wallTopPixel; y < wallBottomPixel; y++)
        {
            /* calcule texture offset Y */
            distanceFromTop = y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
            textureOffsetY = distanceFromTop * ((float)TEXTURE_HEIGHT / wallStripHeight);

            /* setting the color of the wall based on the texture */
            Uint32 texelColor = textures[texNum][(TEXTURE_WIDTH * textureOffsetY) + textureOffsetX];
            colorBuffer[(WINDOW_WIDTH * y) + i] = texelColor;
        }

        /* set the color of floor */
        for (y = wallBottomPixel; y < WINDOW_HEIGHT; y++)
            colorBuffer[(WINDOW_WIDTH * y) + i] = 0xC1C1C1;

        /* This is For replacing the sky with Taller Walls */
        /*for (y = 0; y < wallTopPixel; y++)
        {
            colorBuffer[(WINDOW_WIDTH * y) + i] = rays[i].wasHitVertical ? 0xFFFFFFFF : 0xFFCCCCCC;
        }*/
    }
}