/*
** EPITECH PROJECT, 2022
** mat4x4.h
** File description:
** mat4x4
*/

#ifndef __MAT4X4__
    #define __MAT4X4__

    #include "world.h"

struct Mat4x4 {
    float val[16];
};

typedef struct Mat4x4 Mat4x4;

Mat4x4 *mat4x4_create();
void Mat4x4_destroy(Mat4x4 *mat);

Mat4x4 *mat4x4_MultiplyMat4x4(Mat4x4 *mat1, Mat4x4 *mat2);
float *mat4x4_MultiplyVector4(Mat4x4 *mat, float *vector);
float *mat4x4_MultiplyVector3(Mat4x4 *mat, float *vector, float *res);

Mat4x4 *mat4x4_rx(float a);
Mat4x4 *mat4x4_ry(float a);
Mat4x4 *mat4x4_rz(float a);
Mat4x4 *mat4x4_t(float *vector);
Mat4x4 *mat4x4_scale(float s);

Mat4x4 *mat4x4_invert(float *mat);
void Mat4x4_print(Mat4x4* matrix);

void normalize(float *vec);
float dotProduct3(float *vec1, float *vec2);
void crossProduct3(float *dest, float *vec1, float *vec2);

#endif