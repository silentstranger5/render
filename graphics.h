#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glm.h>
#include <obj.h>
#include <SDL3_image/SDL_image.h>

typedef struct
{
    vec3    **cbuffer;
    float   **dbuffer;
    int     width;
    int     height;
}
graphics_ctx;

typedef struct
{
    vec3    position;
    vec3    normal;
    vec2    texcoord;
    vec3    color;
}
vertex;

typedef struct
{
    vertex v[3];
    vec3 tolight;
    material *mtl;
    SDL_Surface **maps;
}
shader_ctx;

int  graphics_init(graphics_ctx *ctx, int width, int height);
void graphics_clean(graphics_ctx *ctx);
void graphics_triangle(graphics_ctx *ctx, shader_ctx *sctx);
void graphics_free(graphics_ctx *ctx);

#endif
