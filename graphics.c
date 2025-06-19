#include "graphics.h"

static float area(vec3 a, vec3 b, vec3 c)
{
    return -1 * ((a[1] - c[1]) * (b[0] - c[0]) +
                 (b[1] - c[1]) * (c[0] - a[0])) / 2;
}

static void barycentric(vec3 t[3], vec3 p, vec3 d)
{
    float at1 = area(t[1], t[2], p);
    float at2 = area(t[2], t[0], p);
    float at3 = area(t[0], t[1], p);
    if (at1 < 0 || at2 < 0 || at3 < 0)
        return;
    float at = at1 + at2 + at3;
    if (at == 0) return;
    glm_vec3_copy((vec3){at1, at2, at3}, d);
    glm_vec3_scale(d, 1 / at, d);
}

static int intriangle(vec3 v)
{
    return (v[0] >= 0 && v[0] <= 1 &&
            v[1] >= 0 && v[1] <= 1 &&
            v[2] >= 0 && v[2] <= 1);
}

int graphics_init(graphics_ctx *ctx, int width, int height)
{
    if (width <= 0 || height <= 0) return 0;
    memset(ctx, 0, sizeof(graphics_ctx));
    ctx->width = width;
    ctx->height = height;
    ctx->cbuffer = malloc(ctx->height * sizeof(vec3*));
    if (!ctx->cbuffer) return 0;
    memset(ctx->cbuffer, 0, ctx->height * sizeof(vec3*));
    ctx->cbuffer[0] = malloc(ctx->height * ctx->width * sizeof(vec3));
    if (!ctx->cbuffer[0]) return 0;
    memset(ctx->cbuffer[0], 0, ctx->height * ctx->width * sizeof(vec3));
    for (int i = 1; i < ctx->height; i++)
        ctx->cbuffer[i] = ctx->cbuffer[0] + i * ctx->width;
    ctx->dbuffer = malloc(ctx->height * sizeof(float*));
    if (!ctx->dbuffer) return 0;
    memset(ctx->dbuffer, 0, ctx->height * sizeof(float*));
    ctx->dbuffer[0] = malloc(ctx->width * ctx->height * sizeof(float));
    if (!ctx->dbuffer[0]) return 0;
    memset(ctx->dbuffer[0], 0, ctx->height * ctx->width * sizeof(float));
    for (int i = 1; i < ctx->height; i++)
        ctx->dbuffer[i] = ctx->dbuffer[0] + i * ctx->width;
    for (int y = 0; y < ctx->height; y++)
        for (int x = 0; x < ctx->width; x++)
            ctx->dbuffer[y][x] = INFINITY;
    return 1;
}

void graphics_clean(graphics_ctx *ctx)
{
    memset(*ctx->cbuffer, 0, ctx->height * ctx->width * sizeof(vec3));
    for (int y = 0; y < ctx->height; y++)
        for (int x = 0; x < ctx->width; x++)
            ctx->dbuffer[y][x] = INFINITY;
}

void shader(shader_ctx *ctx, vec3 weights, vec3 color)
{
    if (ctx->mtl->mapidx[DIFFUSE] != 0)
    {
        SDL_Surface *surface = ctx->maps[ctx->mtl->mapidx[DIFFUSE] - 1];
        vec3 uvec = {ctx->v[0].texcoord[0], ctx->v[1].texcoord[0], ctx->v[2].texcoord[0]};
        vec3 vvec = {ctx->v[0].texcoord[1], ctx->v[1].texcoord[1], ctx->v[2].texcoord[1]};
        float uval = glm_vec3_dot(weights, uvec);
        float vval = glm_vec3_dot(weights, vvec);
        SDL_ReadSurfacePixelFloat(
            surface, 
            (int) (uval * surface->w), (int) ((1 - vval) * surface->h),
            &color[0], &color[1], &color[2], NULL
        );
    }
    else if (!glm_vec3_eq(ctx->mtl->colors[DIFFUSE], 0))
        glm_vec3_copy(ctx->mtl->colors[DIFFUSE], color);

    vec3 nxvec = {ctx->v[0].normal[0], ctx->v[1].normal[0], ctx->v[2].normal[0]};
    vec3 nyvec = {ctx->v[0].normal[1], ctx->v[1].normal[1], ctx->v[2].normal[1]};
    vec3 nzvec = {ctx->v[0].normal[2], ctx->v[1].normal[2], ctx->v[2].normal[2]};
    float nxval = glm_vec3_dot(weights, nxvec);
    float nyval = glm_vec3_dot(weights, nyvec);
    float nzval = glm_vec3_dot(weights, nzvec);
    vec3 normal = {nxval, nyval, nzval};
    float lval = glm_vec3_dot(normal, ctx->tolight);
    glm_vec3_scale(color, lval, color);
}

void graphics_triangle(graphics_ctx *gctx, shader_ctx *sctx)
{
    vec2 aabb[2] = {0};
    glm_aabb2_empty(aabb);
    for (int i = 0; i < 3; i++)
        glm_aabb2_add(aabb, sctx->v[i].position);
    for (int y = (int) aabb[0][1]; y < aabb[1][1]; y++)
        for (int x = (int) aabb[0][0]; x < aabb[1][0]; x++)
        {
            vec3 color = {0};
            vec3 depths = {0};
            vec3 weights = {0};
            vec3 positions[3] = {0};
            for (int i = 0; i < 3; i++)
            {
                depths[i] = sctx->v[i].position[2];
                glm_vec3_copy(sctx->v[i].position, positions[i]);
            }
            barycentric(positions, (vec3){(float) x, (float) y, 1}, weights);
            if (glm_vec3_eq(weights, 0) || !intriangle(weights))
                continue;
            float depth = glm_vec3_dot(weights, depths);
            if (depth > gctx->dbuffer[y][x]) continue;
            gctx->dbuffer[y][x] = depth;
            shader(sctx, weights, color);
            glm_vec3_copy(color, gctx->cbuffer[y][x]);
        }
}

void graphics_free(graphics_ctx *ctx)
{
    free(*ctx->cbuffer);
    free(*ctx->dbuffer);
    free(ctx->cbuffer);
    free(ctx->dbuffer);
}
