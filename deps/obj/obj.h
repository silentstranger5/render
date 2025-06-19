#ifndef OBJ_H
#define OBJ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>

enum 
{
    AMBIENT,
    DIFFUSE,
    SPECULAR,
    EMISSIVE,
    HIGHLIGHT,
    ALPHA,
    BUMP,
    N
};

typedef struct
{
    char    name[1 << 5];
    char    maps[N][1 << 5];
    int     mapidx[N];
    float   colors[N][3];
    float   shininess;
    float   alpha;
    float   refraction;
}
material;

typedef struct 
{
    char    name[1 << 5];
    char    mtlname[1 << 5];
    array   positions;
    array   normals;
    array   texcoords;
    array   faces;
    float   position[3];
    float   yaw;
    float   pitch;
    float   roll;
    int     mtlidx;
}
model;

typedef struct
{
    array   models;
    array   materials;
}
obj_ctx;

int model_init(model *m);
int objctx_init(obj_ctx *ctx);
void objctx_free(obj_ctx *ctx);
int parse_obj(obj_ctx *ctx, char *filename);
int parse_mtl(obj_ctx *ctx, char *filename);
int lookup(obj_ctx *ctx, char *objname);

#endif
