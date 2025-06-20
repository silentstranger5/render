#include <math.h>
#include "glm.h"

void glm_vec2_scale(vec2 v, float k, vec2 dest)
{
    for (int i = 0; i < 2; i++)
        dest[i] = v[i] * k;
}

void glm_vec2_negate(vec2 v)
{
    glm_vec2_scale(v, -1, v);
}

void glm_vec2_add(vec2 a, vec2 b, vec2 dest)
{
    for (int i = 0; i < 2; i++)
        dest[i] = a[i] + b[i];
}

void glm_vec2_sub(vec2 a, vec2 b, vec2 dest)
{
    for (int i = 0; i < 2; i++)
        dest[i] = a[i] - b[i];
}

float glm_vec2_norm2(vec2 v)
{
    float norm2 = 0;
    for (int i = 0; i < 2; i++)
        norm2 += v[i] * v[i];
    return norm2;
}

float glm_vec2_norm(vec2 v)
{
    return (float) sqrt(glm_vec2_norm2(v));
}

void glm_vec2_normalize(vec2 v)
{
    float norm = glm_vec2_norm(v);
    glm_vec2_scale(v, 1 / norm, v);
}

float glm_vec2_distance2(vec2 a, vec2 b)
{
    vec2 d = {0};
    glm_vec2_sub(b, a, d);
    return glm_vec2_norm2(d);
}

float glm_vec2_distance(vec2 a, vec2 b)
{
    return (float) sqrt(glm_vec2_distance2(a, b));
}

float glm_vec2_dot(vec2 a, vec2 b)
{
    float dot = 0;
    for (int i = 0; i < 2; i++)
        dot += a[i] * b[i];
    return dot;
}

void glm_vec2_zero(vec2 v)
{
    for (int i = 0; i < 2; i++)
        v[i] = 0;
}

void glm_vec2_copy(vec2 a, vec2 d)
{
    for (int i = 0; i < 2; i++)
        d[i] = a[i];
}

void glm_vec2_swap(vec2 a, vec2 b)
{ 
    vec2 t =    {a[0], a[1]}; 
    a =  (vec2) {b[0], b[1]};
    b =  (vec2) {t[0], t[1]};
}

int glm_vec2_eq(vec2 v, float val)
{
    int eq = 1;
    for (int i = 0; i < 2; i++)
        eq &= (v[i] == val);
    return eq;
}

void glm_vec3_scale(vec3 v, float k, vec3 dest)
{
    for (int i = 0; i < 3; i++)
        dest[i] = v[i] * k;
}

void glm_vec3_negate(vec3 v)
{
    glm_vec3_scale(v, -1, v);
}

void glm_vec3_add(vec3 a, vec3 b, vec3 dest)
{
    for (int i = 0; i < 3; i++)
        dest[i] = a[i] + b[i];
}

void glm_vec3_sub(vec3 a, vec3 b, vec3 dest)
{
    for (int i = 0; i < 3; i++)
        dest[i] = a[i] - b[i];
}

float glm_vec3_norm2(vec3 v)
{
    float norm2 = 0;
    for (int i = 0; i < 3; i++)
        norm2 += v[i] * v[i];
    return norm2;
}

float glm_vec3_norm(vec3 v)
{
    return (float) sqrt(glm_vec3_norm2(v));
}

void glm_vec3_normalize(vec3 v)
{
    float norm = glm_vec3_norm(v);
    glm_vec3_scale(v, 1 / norm, v);
}

float glm_vec3_distance2(vec3 a, vec3 b)
{
    vec2 d = {0};
    glm_vec3_sub(b, a, d);
    return glm_vec3_norm2(d);
}

float glm_vec3_distance(vec3 a, vec3 b)
{
    return (float) sqrt(glm_vec3_distance2(a, b));
}

float glm_vec3_dot(vec3 a, vec3 b)
{
    float dot = 0;
    for (int i = 0; i < 3; i++)
        dot += a[i] * b[i];
    return dot;
}

void glm_vec3_cross(vec3 a, vec3 b, vec3 dest)
{
    glm_vec3_copy((vec3) {
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0],
    }, dest);
}

void glm_vec3_zero(vec3 v)
{
    for (int i = 0; i < 3; i++)
        v[i] = 0;
}
void glm_vec3_copy(vec3 a, vec3 d)
{
    for (int i = 0; i < 3; i++)
        d[i] = a[i];
}

void glm_vec3_swap(vec3 a, vec3 b)
{
    vec3 t = {a[0], a[1], a[2]};
    glm_vec3_copy(b, a);
    glm_vec3_copy(t, b);
}

int glm_vec3_eq(vec3 v, float val)
{
    int eq = 1;
    for (int i = 0; i < 3; i++)
        eq &= (v[i] == val);
    return eq;
}

void glm_vec4_scale(vec4 v, float k, vec4 dest)
{
    for (int i = 0; i < 4; i++)
        dest[i] = v[i] * k;
}

void glm_vec4_negate(vec4 v)
{
    glm_vec4_scale(v, -1, v);
}

void glm_vec4_add(vec4 a, vec4 b, vec4 dest)
{
    for (int i = 0; i < 4; i++)
        dest[i] = a[i] + b[i];
}

void glm_vec4_sub(vec4 a, vec4 b, vec4 dest)
{
    for (int i = 0; i < 4; i++)
        dest[i] = a[i] - b[i];
}

float glm_vec4_norm2(vec4 v)
{
    float norm2 = 0;
    for (int i = 0; i < 4; i++)
        norm2 += v[i] * v[i];
    return norm2;
}

float glm_vec4_norm(vec4 v)
{
    return (float) sqrt(glm_vec4_norm2(v));
}

void glm_vec4_normalize(vec4 v)
{
    float norm = glm_vec4_norm(v);
    glm_vec4_scale(v, 1 / norm, v);
}

float glm_vec4_distance2(vec4 a, vec4 b)
{
    vec2 d = {0};
    glm_vec4_sub(b, a, d);
    return glm_vec4_norm2(d);
}

float glm_vec4_distance(vec4 a, vec4 b)
{
    return (float) sqrt(glm_vec4_distance2(a, b));
}

float glm_vec4_dot(vec4 a, vec4 b)
{
    float dot = 0;
    for (int i = 0; i < 4; i++)
        dot += a[i] * b[i];
    return dot;
}

void glm_vec4_zero(vec4 v)
{
    for (int i = 0; i < 4; i++)
        v[i] = 0;
}

void glm_vec4_copy(vec4 a, vec4 d)
{
    for (int i = 0; i < 4; i++)
        d[i] = a[i];
}

void glm_vec4_swap(vec4 a, vec4 b)
{
    vec4 t = {a[0], a[1], a[2], a[3]};
    glm_vec4_copy(b, a);
    glm_vec4_copy(t, b);
}

int glm_vec4_eq(vec4 v, float val)
{
    int eq = 1;
    for (int i = 0; i < 4; i++)
        eq &= (v[i] == val);
    return eq;
}

void glm_mat2_zero(mat2 m)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            m[i][j] = 0;
}

void glm_mat2_identity(mat2 m)
{
    m = (mat2) {0};
    for (int i = 0; i < 2; i++)
        m[i][i] = 1;
}

void glm_mat2_copy(mat2 m, mat2 d)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            d[i][j] = m[i][j];
}

void glm_mat2_transpose(mat2 m)
{
    mat2 t = {0};
    glm_mat2_copy(m, t);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            m[i][j] = t[j][i];
}

void glm_mat2_scale(mat2 m, float s)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            m[i][j] *= s;
}

void glm_mat2_mul(mat2 m1, mat2 m2, mat2 dest)
{
    mat2 t = {0};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                t[i][j] += m1[i][k] * m2[k][j];
    glm_mat2_copy(t, dest);
}

void glm_mat2_mulv(mat2 m, vec2 v, vec2 d)
{
    vec2 t = {0};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            t[i] += m[i][j] * v[j];
    glm_vec2_copy(t, d);
}

float glm_mat2_det(mat2 m)
{
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

void glm_mat3_zero(mat3 m)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] = 0;
}

void glm_mat3_identity(mat3 m)
{
    m = (mat3) {0};
    for (int i = 0; i < 3; i++)
        m[i][i] = 1;
}

void glm_mat3_copy(mat3 m, mat3 d)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            d[i][j] = m[i][j];
}

void glm_mat3_transpose(mat3 m)
{
    mat3 t = {0};
    glm_mat3_copy(m, t);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] = t[j][i];
}

void glm_mat3_scale(mat3 m, float s)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] *= s;
}

void glm_mat3_mul(mat3 m1, mat3 m2, mat3 dest)
{
    mat3 t = {0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                t[i][j] += m1[i][k] * m2[k][j];
    glm_mat3_copy(t, dest);
}

void glm_mat3_mulv(mat3 m, vec3 v, vec3 d)
{
    vec3 t = {0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            t[i] += m[i][j] * v[j];
    glm_vec3_copy(t, d);
}

float glm_mat3_det(mat3 m)
{
    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
        +  m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2])
        +  m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

void glm_mat4_zero(mat4 m)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = 0;
}

void glm_mat4_identity(mat4 m)
{
    glm_mat4_zero(m);
    for (int i = 0; i < 4; i++)
        m[i][i] = 1;
}

void glm_mat4_copy(mat4 m, mat4 d)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            d[i][j] = m[i][j];
}

void glm_mat4_transpose(mat4 m)
{
    mat4 t = {0};
    glm_mat4_copy(m, t);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = t[j][i];
}

void glm_mat4_scale(mat4 m, float s)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] *= s;
}

void glm_mat4_mul(mat4 m1, mat4 m2, mat4 dest)
{
    mat4 t = {0};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                t[i][j] += m1[i][k] * m2[k][j];
    glm_mat4_copy(t, dest);
}

void glm_mat4_mulv(mat4 m, vec4 v, vec4 d)
{
    vec4 t = {0};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            t[i] += m[i][j] * v[j];
    glm_vec4_copy(t, d);
}

void glm_translate2d(mat3 m, vec2 v)
{
    mat3 t = {
        { 1, 0, v[0] },
        { 0, 1, v[1] },
        { 0, 0, 1 },
    };
    glm_mat3_mul(m, t, m);
}

void glm_scale2d(mat3 m, vec2 v)
{
    mat3 t = {
        { v[0], 0, 0 },
        { 0, v[1], 0 },
        { 0, 0, 1 },
    };
    glm_mat3_mul(m, t, m);
}

void glm_rotate2d(mat3 m, float theta)
{
    mat3 t = {
        { (float)  cos(theta), (float) sin(theta), 0 },
        { (float) -sin(theta), (float) cos(theta), 0 },
        {  0, 0, 1 },
    };
    glm_mat3_mul(m, t, m);
}

void glm_translate(mat4 m, vec3 v)
{
    mat4 t = {
        { 1, 0, 0, v[0] },
        { 0, 1, 0, v[1] },
        { 0, 0, 1, v[2] },
        { 0, 0, 0, 1 },
    };
    glm_mat4_mul(m, t, m);
}

void glm_scale(mat4 m, vec3 v)
{
    mat4 t = {
        { v[0], 0, 0, 0 },
        { 0, v[1], 0, 0 },
        { 0, 0, v[2], 0 },
        { 0, 0, 0, 1 },
    };
    glm_mat4_mul(m, t, m);
}

void glm_rotate_x(mat4 m, float theta)
{
    mat4 t = {
        {   1,  0,                  0,                      0   },
        {   0,  (float) cos(theta), (float) -sin(theta),    0   },
        {   0,  (float) sin(theta), (float)  cos(theta),    0   },
        {   0,  0,                  0,                      1   },
    };
    glm_mat4_mul(m, t, m);
}

void glm_rotate_y(mat4 m, float theta)
{
    mat4 t = {
        {   (float) cos(theta),     0,  (float) sin(theta), 0   },
        {   0,                      1,  0,                  0   },
        {   (float) -sin(theta),    0,  (float) cos(theta), 0   },
        {   0,                      0,  0,                  1   },
    };
    glm_mat4_mul(m, t, m);
}

void glm_rotate_z(mat4 m, float theta)
{
    mat4 t = {
        {   (float) cos(theta),    (float) -sin(theta), 0,  0   },
        {   (float) sin(theta),    (float)  cos(theta), 0,  0   },
        {   0,              0,          1,  0   },
        {   0,              0,          0,  1   },
    };
    glm_mat4_mul(m, t, m);
}

void glm_lookat(vec3 eye, vec3 center, vec3 up, mat4 d)
{
    vec3 f, s, u;
    glm_vec3_sub(center, eye, f);
    glm_vec3_normalize(f);
    glm_vec3_cross(up, f, s);
    glm_vec3_normalize(s);
    glm_vec3_cross(f, s, u);
    mat4 m = {
        {s[0],  s[1],   s[2],   0},
        {u[0],  u[1],   u[2],   0},
        {f[0],  f[1],   f[2],   0},
        {0,     0,      0,      1},
    };
    glm_mat4_mul(d, m, d);
    glm_translate(d, (vec3){-eye[0], -eye[1], -eye[2]});
}

void glm_ortho(float left, float right, float bottom, float top, float near, float far, mat4 d)
{
    float zoomx = 2 / (right - left);
    float zoomy = 2 / (top - bottom);
    mat4 t = {
        {   zoomx,  0,      0,  0   },
        {   0,      zoomy,  0,  0   },
        {   0,  0,  2 / (far - near),   -1 * (far + near) / (far - near) },
        {   0,  0,          0,  1   },
    };
    glm_mat4_mul(d, t, d);
}

void glm_perspective(float fovy, float aspect, float near, float far, mat4 d)
{
    float zoomy = 1 / (float) tan(fovy / 2);
    float zoomx = zoomy / aspect;
    mat4 t = {
        {   zoomx,  0,  0,  0   },
        {   0,  zoomy,  0,  0   },
        {   0,  0,  (far + near) / (far - near),    (-2 * far * near) / (far - near)    },
        {   0,  0,      1,  0   },
    };
    glm_mat4_mul(d, t, d);
}

void glm_aabb2_empty(vec2 aabb[2])
{
    for (int i = 0; i < 2; i++)
    {
        aabb[0][i] =  INFINITY;
        aabb[1][i] = -INFINITY;
    }
}

void glm_aabb2_add(vec2 aabb[2], vec2 v)
{
    for (int i = 0; i < 2; i++)
    {
        if (v[i] < aabb[0][i]) aabb[0][i] = v[i];
        if (v[i] > aabb[1][i]) aabb[1][i] = v[i];
    }
}

void glm_aabb2_crop(vec2 box[2], vec2 crop[2], vec2 dest[2])
{
    for (int i = 0; i < 2; i++)
    {
        dest[0][i] = max(box[0][i], crop[0][i]);
        dest[1][i] = min(box[1][i], crop[1][i]);
    }
}

int glm_aabb2_point(vec2 aabb[2], vec2 v)
{
    return  v[0] >= aabb[0][0] && v[0] <= aabb[1][0] &&
            v[1] >= aabb[0][1] && v[1] <= aabb[1][1];
}

void glm_aabb_empty(vec3 aabb[2])
{
    for (int i = 0; i < 3; i++)
    {
        aabb[0][i] =  INFINITY;
        aabb[1][i] = -INFINITY;
    }
}

void glm_aabb_add(vec3 aabb[2], vec3 v)
{
    for (int i = 0; i < 3; i++)
    {
        if (v[i] < aabb[0][i]) aabb[0][i] = v[i];
        if (v[i] > aabb[1][i]) aabb[1][i] = v[i];
    }
}

void glm_aabb_crop(vec3 box[2], vec3 crop[2], vec3 dest[2])
{
    for (int i = 0; i < 3; i++)
    {
        dest[0][i] = max(box[0][i], crop[0][i]);
        dest[1][i] = min(box[1][i], crop[1][i]);
    }
}

int glm_aabb_point(vec3 aabb[2], vec3 v)
{
    return  v[0] >= aabb[0][0] && v[0] <= aabb[1][0] &&
            v[1] >= aabb[0][1] && v[1] <= aabb[1][1] &&
            v[2] >= aabb[0][2] && v[2] <= aabb[1][2];
}
