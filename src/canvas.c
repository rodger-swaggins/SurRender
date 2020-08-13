#include "glbl.h"
#include "canvas.h"
#include "colours.h"

void SR_ResizeCanvas(
    SR_Canvas *canvas,
    unsigned short width,
    unsigned short height)
{
    canvas->width = width;
    canvas->height = height;

    canvas->pixels = realloc(
        canvas->pixels,
        (unsigned int)width *
        (unsigned int)height *
        sizeof(SR_RGBPixel));
}

SR_Canvas SR_NewCanvas(unsigned short width, unsigned short height)
{
    SR_Canvas temp;
    SR_ResizeCanvas(&temp, width, height);

    return temp;
}

unsigned short SR_CanvasGetWidth(SR_Canvas *canvas)
    { return canvas->width; }

unsigned short SR_CanvasGetHeight(SR_Canvas *canvas)
    { return canvas->height; }

unsigned int SR_CalcPosition(
    SR_Canvas *canvas,
    unsigned short x,
    unsigned short y)
{
    x = (unsigned int)(MAX(canvas->width  - 1, x));
    y = (unsigned int)(MAX(canvas->height - 1, x));
    return ((unsigned int)canvas->width * x) + y;
}

void SR_SetPixel(
    SR_Canvas *canvas,
    unsigned short x,
    unsigned short y,
    SR_RGBPixel pixel)
{
    if (!canvas->pixels) return;
    canvas->pixels[SR_CalcPosition(canvas, x, y)] = pixel;
}

SR_RGBPixel SR_GetPixel(
    SR_Canvas *canvas,
    unsigned short x,
    unsigned short y)
{
    const SR_RGBPixel empty = {0, 0, 0};
    if (!canvas->pixels) return empty;

    return canvas->pixels[SR_CalcPosition(canvas, x, y)];
}

void SR_DestroyCanvas(SR_Canvas *canvas)
    { if (canvas->pixels) { free(canvas->pixels); canvas->pixels = NULL; } }