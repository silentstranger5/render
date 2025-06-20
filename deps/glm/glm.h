#ifndef GLM_H
#define GLM_H

#include <stdlib.h>

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

typedef vec2 mat2[2];
typedef vec3 mat3[3];
typedef vec4 mat4[4];

typedef int ivec2[2];
typedef int ivec3[3];
typedef int ivec4[4];

void glm_vec2_scale(vec2 v, float k, vec2 dest);
void glm_vec2_negate(vec2 v);
void glm_vec2_add(vec2 a, vec2 b, vec2 dest);
void glm_vec2_sub(vec2 a, vec2 b, vec2 dest);
float glm_vec2_norm2(vec2 v);
float glm_vec2_norm(vec2 v);
void glm_vec2_normalize(vec2 v);
float glm_vec2_distance2(vec2 a, vec2 b);
float glm_vec2_distance(vec2 a, vec2 b);
float glm_vec2_dot(vec2 a, vec2 b);
void glm_vec2_zero(vec2 v);
void glm_vec2_copy(vec2 a, vec2 d);
void glm_vec2_swap(vec2 a, vec2 b);
int glm_vec2_eq(vec2 v, float val);

void glm_vec3_scale(vec3 v, float k, vec3 dest);
void glm_vec3_negate(vec3 v);
void glm_vec3_add(vec3 a, vec3 b, vec3 dest);
void glm_vec3_sub(vec3 a, vec3 b, vec3 dest);
float glm_vec3_norm2(vec3 v);
float glm_vec3_norm(vec3 v);
void glm_vec3_normalize(vec3 v);
float glm_vec3_distance2(vec3 a, vec3 b);
float glm_vec3_distance(vec3 a, vec3 b);
float glm_vec3_dot(vec3 a, vec3 b);
void glm_vec3_cross(vec3 a, vec3 b, vec3 dest);
void glm_vec3_zero(vec3 v);
void glm_vec3_copy(vec3 a, vec3 d);
void glm_vec3_swap(vec3 a, vec3 b);
int glm_vec3_eq(vec3 v, float val);

void glm_vec4_scale(vec4 v, float k, vec4 dest);
void glm_vec4_negate(vec4 v);
void glm_vec4_add(vec4 a, vec4 b, vec4 dest);
void glm_vec4_sub(vec4 a, vec4 b, vec4 dest);
float glm_vec4_norm2(vec4 v);
float glm_vec4_norm(vec4 v);
void glm_vec4_normalize(vec4 v);
float glm_vec4_distance2(vec4 a, vec4 b);
float glm_vec4_distance(vec4 a, vec4 b);
float glm_vec4_dot(vec4 a, vec4 b);
void glm_vec4_cross(vec4 a, vec4 b, vec4 dest);
void glm_vec4_zero(vec4 v);
void glm_vec4_copy(vec4 a, vec4 d);
void glm_vec4_swap(vec4 a, vec4 b);
int glm_vec4_eq(vec4 v, float val);

void glm_mat2_zero(mat2 m);
void glm_mat2_identity(mat2 m);
void glm_mat2_copy(mat2 m, mat2 d);
void glm_mat2_transpose(mat2 m);
void glm_mat2_scale(mat2 m, float s);
void glm_mat2_mul(mat2 m1, mat2 m2, mat2 dest);
void glm_mat2_mulv(mat2 m, vec2 v, vec2 d);
float glm_mat2_det(mat2 m);

void glm_mat3_zero(mat3 m);
void glm_mat3_identity(mat3 m);
void glm_mat3_copy(mat3 m, mat3 d);
void glm_mat3_transpose(mat3 m);
void glm_mat3_scale(mat3 m, float s);
void glm_mat3_mul(mat3 m1, mat3 m2, mat3 dest);
void glm_mat3_mulv(mat3 m, vec3 v, vec3 d);
float glm_mat3_det(mat3 m);

void glm_mat4_zero(mat4 m);
void glm_mat4_identity(mat4 m);
void glm_mat4_copy(mat4 m, mat4 d);
void glm_mat4_transpose(mat4 m);
void glm_mat4_scale(mat4 m, float s);
void glm_mat4_mul(mat4 m1, mat4 m2, mat4 dest);
void glm_mat4_mulv(mat4 m, vec4 v, vec4 d);

void glm_translate2d(mat3 m, vec2 v);
void glm_scale2d(mat3 m, vec2 v);
void glm_rotate2d(mat3 m, float theta);

void glm_translate(mat4 m, vec3 v);
void glm_scale(mat4 m, vec3 v);
void glm_rotate_x(mat4 m, float theta);
void glm_rotate_y(mat4 m, float theta);
void glm_rotate_z(mat4 m, float theta);

void glm_lookat(vec3 eye, vec3 center, vec3 up, mat4 d);
void glm_ortho(float left, float right, float bottom, float top, float near, float far, mat4 d);
void glm_perspective(float fovy, float aspect, float near, float far, mat4 d);

void glm_aabb2_empty(vec2 aabb[2]);
void glm_aabb2_add(vec2 aabb[2], vec2 v);
void glm_aabb2_crop(vec2 box[2], vec2 crop[2], vec2 dest[2]);
int glm_aabb2_point(vec2 aabb[2], vec2 v);

void glm_aabb_empty(vec3 aabb[2]);
void glm_aabb_add(vec3 aabb[2], vec3 v);
void glm_aabb_crop(vec3 box[2], vec3 crop[2], vec3 dest[2]);
int glm_aabb_point(vec3 aabb[2], vec3 v);

#endif
