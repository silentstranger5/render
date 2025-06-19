#include "obj.h"

int objctx_init(obj_ctx *ctx)
{
    int ok  = array_init(&ctx->models, sizeof(model));
        ok &= array_init(&ctx->materials, sizeof(material));
    return ok;
}

void objctx_free(obj_ctx *ctx)
{
    for (int i = 0; i < ctx->models.size; i++)
    {
        model *mod = array_get(&ctx->models, i);
        array_free(&mod->positions);
        array_free(&mod->normals);
        array_free(&mod->texcoords);
        array_free(&mod->faces);
    }
    array_free(&ctx->models);
    array_free(&ctx->materials);
}

int model_init(model *m)
{
    memset(m, 0, sizeof(model));
    int ok  = array_init(&m->positions, 3 * sizeof(float));
        ok &= array_init(&m->normals, 3 * sizeof(float));
        ok &= array_init(&m->texcoords, 2 * sizeof(float));
        ok &= array_init(&m->faces, 3 * sizeof(int));
    if (!ok)
    {
        printf("failed to init model: array initialization failure\n");
        return 0;
    }
    return 1;
}

int parse_obj(obj_ctx *ctx, char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        printf("failed to parse obj file: file does not exist\n");
        return 0;
    }
    char s[1 << 4];
    model mod = {0};
    while (fscanf(f, "%s", s) > 0)
    {
        if (!strcmp(s, "o"))
        {
            if (ctx->models.size > 0)
            {
                int ok = array_push(&ctx->models, &mod);
                if (!ok)
                {
                    printf("failed to parse obj file: memory allocation failure\n");
                    return 0;
                }
            }
            int ok = model_init(&mod);
            if (!ok)
            {
                printf("failed to parse obj file: model initialization failure\n");
                return 0;
            }
            int fields = fscanf(f, "%s\n", mod.name);
            if (fields < 1)
            {
                printf("failed to parse obj file: invalid name format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "v"))
        {
            float position[3] = {0};
            int fields = fscanf(f, "%f %f %f\n", 
                &position[0],
                &position[1],
                &position[2]
            );
            if (fields < 3)
            {
                printf("failed to parse obj file: invalid position format\n");
                return 0;
            }
            int ok = array_push(&mod.positions, &position);
            if (!ok)
            {
                printf("failed to parse obj file: memory allocation failure\n");
                return 0;
            }
        }
        else if (!strcmp(s, "vn"))
        {
            float normal[3] = {0};
            int fields = fscanf(f, "%f %f %f\n",
                &normal[0],
                &normal[1],
                &normal[2]
            );
            if (fields < 3)
            {
                printf("failed to parse obj file: invalid normal format\n");
                return 0;
            }
            int ok = array_push(&mod.normals, &normal);
            if (!ok)
            {
                printf("failed to parse obj file: memory allocation failure\n");
                return 0;
            }
        }
        else if (!strcmp(s, "vt"))
        {
            float texcoord[2] = {0};
            int fields = fscanf(f, "%f %f\n",
                &texcoord[0],
                &texcoord[1]
            );
            if (fields < 2)
            {
                printf("failed to parse obj file: invalid texcoord format\n");
                return 0;
            }
            int ok = array_push(&mod.texcoords, &texcoord);
            if (!ok)
            {
                printf("failed to parse obj file: memory allocation failure\n");
                return 0;
            }
        }
        else if (!strcmp(s, "f"))
        {
            int faces[3][3] = {0};
            int fields = fscanf(
                f, 
                "%d/%d/%d "
                "%d/%d/%d "
                "%d/%d/%d\n",
                &faces[0][0],
                &faces[0][1],
                &faces[0][2],
                &faces[1][0],
                &faces[1][1],
                &faces[1][2],
                &faces[2][0],
                &faces[2][1],
                &faces[2][2]
            );
            if (fields < 9)
            {
                printf("failed to parse obj file: invalid face format\n");
                return 0;
            }
            int ok  = array_push(&mod.faces, &faces[0]);
                ok &= array_push(&mod.faces, &faces[1]);
                ok &= array_push(&mod.faces, &faces[2]);
            if (!ok)
            {
                printf("failed to parse obj file: memory allocation failure\n");
                return 0;
            }
        }
        else if (!strcmp(s, "mtllib"))
        {
            char filepath[1 << 6];
            if (strchr(filename, '/'))
            {
                strcpy(filepath, filename);
                char *mtlfname = strrchr(filepath, '/') + 1;
                int fields = fscanf(f, "%s\n", mtlfname);
                if (fields < 1)
                {
                    printf("failed to parse mtl file: invalid mtl filename format\n");
                    return 0;
                }
            }
            else
            {
                int fields = fscanf(f, "%s\n", filepath);
                if (fields < 1)
                {
                    printf("failed to parse mtl file: invalid mtl filename format\n");
                    return 0;
                }
            }
            int ok = parse_mtl(ctx, filepath);
            if (!ok)
            {
                printf("failed to parse obj file: material parsing failure\n");
                return 0;
            }
        }
        else if (!strcmp(s, "usemtl"))
        {
            int fields = fscanf(f, "%s\n", mod.mtlname);
            if (fields < 1)
            {
                printf("failed to parse obj file: invalid material name format\n");
                return 0;
            }
        }
        else
        {
            char str[1 << 10];
            fgets(str, (1 << 10), f);
        }
    }
    int ok = array_push(&ctx->models, &mod);
    if (!ok)
    {
        printf("failed to parse obj file: memory allocation failure\n");
        return 0;
    }
    for (int i = 0; i < ctx->models.size; i++)
        for (int j = 0; j < ctx->materials.size; j++)
        {
            model *mod = array_get(&ctx->models, i);
            if (!mod) return 0;
            material *mtl = array_get(&ctx->materials, j);
            if (!mtl) return 0;
            if (!strcmp(mod->mtlname, mtl->name))
                mod->mtlidx = j;
        }
    fclose(f);
    return 1;
}

int parse_mtl(obj_ctx *ctx, char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        printf("failed to parse mtl file: file does not exist\n");
        return 0;
    }
    char s[16];
    material mtl = {0};
    material *mtlptr = &mtl;
    while (fscanf(f, "%s", s) > 0)
    {
        if (!strcmp(s, "newmtl"))
        {
            if (ctx->materials.size > 0)
            {
                int ok = array_push(&ctx->materials, mtlptr);
                if (!ok)
                {
                    printf("failed to parse mtl file: memory allocation failure\n");
                    return 0;
                }
            }
            memset(mtlptr, 0, sizeof(material));
            int fields = fscanf(f, "%s\n", mtlptr->name);
            if (fields == 0)
            {
                printf("failed to parse mtl file: invalid name format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "Ka"))
        {
            int fields = fscanf(f, "%f %f %f\n",
                &mtlptr->colors[AMBIENT][0],
                &mtlptr->colors[AMBIENT][1],
                &mtlptr->colors[AMBIENT][2]
            );
            if (fields < 3)
            {
                printf("failed to parse mtl file: invalid ambient color format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "Kd"))
        {
            int fields = fscanf(f, "%f %f %f\n",
                &mtlptr->colors[DIFFUSE][0],
                &mtlptr->colors[DIFFUSE][1],
                &mtlptr->colors[DIFFUSE][2]
            );
            if (fields < 3)
            {
                printf("failed to parse mtl file: invalid diffuse color format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "Ks"))
        {
            int fields = fscanf(f, "%f %f %f\n",
                &mtlptr->colors[SPECULAR][0],
                &mtlptr->colors[SPECULAR][1],
                &mtlptr->colors[SPECULAR][2]
            );
            if (fields < 3)
            {
                printf("failed to parse mtl file: invalid specular color format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "Ke"))
        {
            int fields = fscanf(f, "%f %f %f\n",
                &mtlptr->colors[EMISSIVE][0],
                &mtlptr->colors[EMISSIVE][1],
                &mtlptr->colors[EMISSIVE][2]
            );
            if (fields < 3)
            {
                printf("failed to parse mtl file: invalid emmissive color format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "Ns"))
        {
            int fields = fscanf(f, "%f\n", &mtlptr->shininess);
            if (fields < 1)
            {
                printf("failed to parse mtl file: invalid specular exponent format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "d"))
        {
            int fields = fscanf(f, "%f\n", &mtlptr->alpha);
            if (fields < 1)
            {
                printf("failed to parse mtl file: invalid dissolve value format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "Ni"))
        {
            int fields = fscanf(f, "%f\n", &mtlptr->refraction);
            if (fields < 1)
            {
                printf("failed to parse mtl file: invalid optical density format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "map_Ka"))
        {
            int fields = fscanf(f, "%s\n", mtlptr->maps[AMBIENT]);
            if (fields < 1)
            {
                printf("failed to parse mtl file: invalid ambient map format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "map_Kd"))
        {
            int fields = fscanf(f, "%s\n", mtlptr->maps[DIFFUSE]);
            if (fields < 1)
            {
                printf("failed to parse mtl file: invalid diffuse map format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "map_Ks"))
        {
            int fields = fscanf(f, "%s\n", mtlptr->maps[SPECULAR]);
            if (fields < 1)
            {
                printf("failed to parse mtl file: invalid specular map format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "map_Ns"))
        {
            int fields = fscanf(f, "%s\n", mtlptr->maps[HIGHLIGHT]);
            if (fields < 1)
            {
                printf("failed to parse mtl file: invalid highlight map format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "map_d"))
        {
            int fields = fscanf(f, "%s\n", mtlptr->maps[ALPHA]);
            if (fields < 1)
            {
                printf("failed to parse mtl file: invalid alpha map format\n");
                return 0;
            }
        }
        else if (!strcmp(s, "map_bump"))
        {
            int fields = fscanf(f, "%s\n", mtlptr->maps[BUMP]);
            if (fields < 1)
            {
                printf("failed to parse mtl file: invalid bump map format\n");
                return 0;
            }
        }
        else
        {
            char str[1 << 10];
            fgets(str, (1 << 10), f);
        }
    }
    int ok = array_push(&ctx->materials, mtlptr);
    if (!ok)
    {
        printf("failed to parse mtl file: memory allocation failure\n");
        return 0;
    }
    fclose(f);
    return 1;
}

int lookup(obj_ctx *ctx, char *objname)
{
    for (int i = 0; i < ctx->models.size; i++)
    {
        model *mod = array_get(&ctx->models, i);
        if (!mod) return -1;
        if (!strcmp(objname, mod->name))
            return i;
    }
    return -1;
}
