/*
** EPITECH PROJECT, 2022
** mat_create2.c
** File description:
** mat_create2
*/

#include "world.h"

float dotProduct3(float *vec1, float *vec2)
{
    return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
}

void crossProduct3(float *dest, float *vec1, float *vec2)
{
    dest[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    dest[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    dest[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

Mat4x4 *mat4x4_scale(float s)
{
    Mat4x4 *mat = mat4x4_create();

    mat->val[0] = s;
    mat->val[5] = s;
    mat->val[10] = s;
    mat->val[15] = 1;
    return mat;
}

Mat4x4 *mat4x4_create()
{
    Mat4x4 *mat = malloc(sizeof(Mat4x4));

    memset(mat, 0, sizeof(Mat4x4));
    mat->val[0] = 1;
    mat->val[5] = 1;
    mat->val[10] = 1;
    mat->val[15] = 1;
    return mat;
}

void Mat4x4_destroy(Mat4x4 *mat)
{
    free(mat);
}
