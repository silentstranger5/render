#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <glm.h>
#include <obj.h>
#include <array.h>
#include <graphics.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#define WIDTH   640
#define HEIGHT  480
#define OBJFILE "../../res/teapot.obj"

#define M_PI    3.14159265358979323846

struct
{
    SDL_Window*     window;
    SDL_Renderer*   renderer;
    array           maps;
}
app_ctx;

struct
{
    vec3    position;
    vec3    direction;
    vec3    up;
    float   yaw;
    float   roll;
    float   pitch;
    float   fovy;
    float   speed;
    int     wasd;
}
camera;

vec3 light = {1, 0, 0};

obj_ctx octx;
graphics_ctx gctx;

int render(void)
{
    mat4 proj_m  = {0};
    mat4 view_m  = {0};
    glm_mat4_identity(proj_m);
    glm_mat4_identity(view_m);
    float aspect = (float) WIDTH / HEIGHT;
    float fovy = camera.fovy * (float) M_PI / 180;
    glm_perspective(fovy, aspect, 0.1f, 10, proj_m);
    vec3 center = {0};
    glm_vec3_add(camera.position, camera.direction, center);
    glm_lookat(camera.position, center, (vec3){0, 1, 0}, view_m);
    for (int i = 0; i < octx.models.size; i++)
    {
        model *mod = array_get(&octx.models, i);
        if (!mod) return 0;
        mat4 model_m = {0};
        glm_mat4_identity(model_m);
        glm_translate(model_m, mod->position);
        glm_rotate_z(model_m, mod->roll * (float) M_PI / 180);
        glm_rotate_x(model_m, mod->pitch * (float) M_PI / 180);
        glm_rotate_y(model_m, mod->yaw * (float) M_PI / 180);
        mat4 trans_m = {0};
        glm_mat4_identity(trans_m);
        glm_mat4_mul(proj_m, view_m, trans_m);
        glm_mat4_mul(trans_m, model_m, trans_m);
        material* mtl = array_get(&octx.materials, mod->mtlidx);
        shader_ctx sctx = {{0}, {0}, mtl, (SDL_Surface**) app_ctx.maps.data};
        glm_vec3_scale(light, -1, sctx.tolight);
        for (int j = 0; j < mod->faces.size; j += 3)
        {
            for (int k = 0; k < 3; k++)
            {
                ivec3 indices = {0};
                vertex *vertex = &sctx.v[k];
                memcpy(indices, array_get(&mod->faces, j + k), sizeof(ivec3));
                if (!indices) return 0;
                for (int t = 0; t < 3; t++) indices[t] -= 1;
                memcpy(vertex->position, array_get(&mod->positions, indices[0]), sizeof(vec3));
                memcpy(vertex->texcoord, array_get(&mod->texcoords, indices[1]), sizeof(vec2));
                memcpy(vertex->normal, array_get(&mod->normals, indices[2]), sizeof(vec3));
                vec4 vec = {0, 0, 0, 1};
                glm_vec3_copy(vertex->position, vec);
                glm_mat4_mulv(trans_m, vec, vec);
                glm_vec4_scale(vec, 1 / vec[3], vec);
                glm_vec3_copy(vec, vertex->position);
                glm_vec4_zero(vec);
                glm_vec3_copy(vertex->normal, vec);
                glm_mat4_mulv(model_m, vec, vec);
                glm_vec3_normalize(vec);
                glm_vec3_copy(vec, vertex->normal);
            }
            vec3 bbox[2] = {
                {-1 * aspect, -1, -1},
                {+1 * aspect, +1, +1},
            };
            int inbounds = 0;
            for (int k = 0; k < 3; k++)
                inbounds |= glm_aabb_point(bbox, sctx.v[k].position);
            if (!inbounds) continue;
            for (int k = 0; k < 3; k++)
            {
                sctx.v[k].position[0] =  sctx.v[k].position[0] * WIDTH  / 2 + WIDTH  / 2;
                sctx.v[k].position[1] = -sctx.v[k].position[1] * HEIGHT / 2 + HEIGHT / 2;
                sctx.v[k].normal[1]   = -sctx.v[k].normal[1];
            }
            graphics_triangle(&gctx, &sctx);
        }
    }
    SDL_Surface *surface = SDL_GetWindowSurface(app_ctx.window);
    SDL_ConvertPixels(
        surface->w, surface->h, SDL_PIXELFORMAT_RGB96_FLOAT, 
        *gctx.cbuffer, surface->w * sizeof(vec3),
        surface->format, surface->pixels, surface->w * sizeof(uint32_t)
    );
    SDL_UpdateWindowSurface(app_ctx.window);
    graphics_clean(&gctx);
    return 1;
}

void camera_update(float dt)
{
    vec4 direction = {0, 0, 1, 1};
    mat4 rot = {0};
    glm_mat4_identity(rot);
    glm_rotate_y(rot, camera.yaw * (float) M_PI / 180);
    glm_rotate_x(rot, camera.pitch * (float) M_PI / 180);
    glm_rotate_z(rot, camera.roll * (float) M_PI / 180);
    glm_mat4_mulv(rot, direction, direction);
    glm_vec3_normalize(direction);
    glm_vec3_copy(direction, camera.direction);
    float dirx = (camera.wasd & (1 << 3) ? 1.0f : 0.0f) 
        - (camera.wasd & (1 << 1) ? 1.0f : 0.0f);
    float diry = (camera.wasd & (1 << 4) ? 1.0f : 0.0f) 
        - (camera.wasd & (1 << 5) ? 1.0f : 0.0f);
    float dirz = (camera.wasd & (1 << 0) ? 1.0f : 0.0f) 
        - (camera.wasd & (1 << 2) ? 1.0f : 0.0f);
    vec3 front = {0};
    vec3 right = {0};
    vec3 up = {0, 1, 0};
    glm_vec3_copy(camera.direction, front);
    glm_vec3_cross(up, front, right);
    glm_vec3_scale(right, dirx * dt * camera.speed, right);
    glm_vec3_scale(up, diry * dt * camera.speed, up);
    glm_vec3_scale(front, dirz * dt * camera.speed, front);
    glm_vec3_add(camera.position, front, camera.position);
    glm_vec3_add(camera.position, right, camera.position);
    glm_vec3_add(camera.position, up, camera.position);
}

int app_init(void)
{
    SDL_SetAppMetadata("Render", "1.0", "com.render");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Failed to init SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("render", WIDTH, HEIGHT, 0, &app_ctx.window, &app_ctx.renderer))
    {
        SDL_Log("Failed to init window / renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetWindowRelativeMouseMode(app_ctx.window, true);

    int ok = objctx_init(&octx);
    if (!ok) return SDL_APP_FAILURE;
    
    ok = parse_obj(&octx, OBJFILE);
    if (!ok) return SDL_APP_FAILURE;
    model *mod = array_get(&octx.models, 0);
    glm_vec3_copy((vec3){0, 0, 5}, mod->position);
    
    ok = graphics_init(&gctx, WIDTH, HEIGHT);
    if (!ok) return SDL_APP_FAILURE;

    int mapidx = 1;
    ok = array_init(&app_ctx.maps, sizeof(SDL_Surface*));
    if (!ok) return SDL_APP_FAILURE;
    
    for (int i = 0; i < octx.materials.size; i++)
    {
        material *mtl = array_get(&octx.materials, i);
        if (!mtl)
        {
            printf("failed to initialize maps: material array out of bounds\n");
            return SDL_APP_FAILURE;
        }
        char s[1 << 10];
        strcpy(s, OBJFILE);
        char *sptr = strrchr(s, '/');
        if (sptr) sptr++;
        else sptr = s;
        *sptr = 0;
        for (int j = 0; j < N; j++)
            if (strlen(mtl->maps[j]) > 0)
            {
                strcat(s, mtl->maps[j]);
                SDL_Surface *surface = IMG_Load(s);
                *sptr = 0;
                if (!surface)
                {
                    printf("failed to initialize maps: texture file does not exist\n");
                    return SDL_APP_FAILURE;
                }
                int ok = array_push(&app_ctx.maps, &surface);
                if (!ok)
                {
                    printf("failed to initialize maps: memory allocation failure\n");
                    return SDL_APP_FAILURE;
                }
                mtl->mapidx[j] = mapidx++;
            }
    }
    
    camera.fovy = 90;
    camera.speed = 5.0f;

    return SDL_APP_CONTINUE;
}

int app_event(SDL_Event *event)
{
    void key_event(int, int);
    void mouse_event(float, float);

    switch (event->type)
    {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
            break;
        case SDL_EVENT_KEY_UP:
        case SDL_EVENT_KEY_DOWN:
            key_event(event->type, event->key.scancode);
            break;
        case SDL_EVENT_MOUSE_MOTION:
            mouse_event(event->motion.xrel, event->motion.yrel);
            break;
    }
    return SDL_APP_CONTINUE;
}

int app_iterate(void)
{
    static uint64_t last = 0;
    uint64_t now = SDL_GetTicks();
    float dt = (float) (now - last) / 1000;
    last = now;
    camera_update(dt);
    render();
    model *mod = array_get(&octx.models, 0);
    mod->yaw++;
    return SDL_APP_CONTINUE;
}

void app_quit(void) 
{
    objctx_free(&octx);
    graphics_free(&gctx);
    SDL_Quit();
}

void key_event(int type, int key_code)
{
    if (type == SDL_EVENT_KEY_DOWN)
    {
        switch (key_code)
        {
            case SDL_SCANCODE_W:
                camera.wasd |= 1 << 0;
                break;
            case SDL_SCANCODE_A:
                camera.wasd |= 1 << 1;
                break;
            case SDL_SCANCODE_S:
                camera.wasd |= 1 << 2;
                break;
            case SDL_SCANCODE_D:
                camera.wasd |= 1 << 3;
                break;
            case SDL_SCANCODE_Q:
                camera.wasd |= 1 << 4;
                break;
            case SDL_SCANCODE_E:
                camera.wasd |= 1 << 5;
                break;
            case SDL_SCANCODE_Z:
                camera.fovy -= 15;
                if (camera.fovy < 15)
                    camera.fovy = 15;
                break;
            case SDL_SCANCODE_X:
                camera.fovy += 15;
                if (camera.fovy > 90)
                    camera.fovy = 90;
                break;
            case SDL_SCANCODE_ESCAPE:
                SDL_Event event;
                event.type = SDL_EVENT_QUIT;
                SDL_PushEvent(&event);
                break;
        }
    }
    else if (type == SDL_EVENT_KEY_UP)
    {
        switch (key_code)
        {
            case SDL_SCANCODE_W:
                camera.wasd &= ~(1 << 0);
                break;
            case SDL_SCANCODE_A:
                camera.wasd &= ~(1 << 1);
                break;
            case SDL_SCANCODE_S:
                camera.wasd &= ~(1 << 2);
                break;
            case SDL_SCANCODE_D:
                camera.wasd &= ~(1 << 3);
                break;
            case SDL_SCANCODE_Q:
                camera.wasd &= ~(1 << 4);
                break;
            case SDL_SCANCODE_E:
                camera.wasd &= ~(1 << 5);
                break;
        }
    }
}

void mouse_event(float xrel, float yrel)
{
    camera.yaw += xrel * 0.1f;
    camera.pitch += yrel * 0.1f;
}

int main(int argc, char **argv)
{
    int status = app_init();
    if (status != SDL_APP_CONTINUE)
        return status;

    SDL_Event e;
    bool done = false;
    while ((status = app_iterate()) == SDL_APP_CONTINUE && !done)
        while (SDL_PollEvent(&e) != 0)
            if ((status = app_event(&e)) != SDL_APP_CONTINUE)
                done = true;

    app_quit();
    return (status == SDL_APP_SUCCESS) ? 0 : status;
}
