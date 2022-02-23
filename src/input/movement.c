/*
** EPITECH PROJECT, 2022
** movement.c
** File description:
** movement
*/

#include "world.h"

void move_player(Mat4x4 **matWorld)
{
    Mat4x4 *matMov;
    Mat4x4 *tmp;
    float vec[3] = {0, 0, 0};
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        vec[2] = 0.5;
    if (sfKeyboard_isKeyPressed(sfKeyS))
        vec[2] = -0.5;
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        vec[0] = -0.5;
    if (sfKeyboard_isKeyPressed(sfKeyD))
        vec[0] = 0.5;
    if (sfKeyboard_isKeyPressed(sfKeyA))
        vec[1] = 0.5;
    if (sfKeyboard_isKeyPressed(sfKeyE))
        vec[1] = -0.5;
    matMov = mat4x4_t(vec);
    tmp = mat4x4_MultiplyMat4x4(*matWorld, matMov);
    Mat4x4_destroy(matMov);
    Mat4x4_destroy(*matWorld);
    *matWorld = tmp;
}

void move_cam(Mat4x4 **matWorld)
{
    Mat4x4 *tmp;
    Mat4x4 *matMov = NULL;

    if (sfKeyboard_isKeyPressed(sfKeyJ))
        matMov = mat4x4_ry(-PI/180);
    if (sfKeyboard_isKeyPressed(sfKeyL))
        matMov = mat4x4_ry(PI/180);
    if (sfKeyboard_isKeyPressed(sfKeyI))
        matMov = mat4x4_rx(-PI/180);
    if (sfKeyboard_isKeyPressed(sfKeyK))
        matMov = mat4x4_rx(PI/180);
    if (matMov != NULL) {
        tmp = mat4x4_MultiplyMat4x4(*matWorld, matMov);
        Mat4x4_destroy(matMov);
        Mat4x4_destroy(*matWorld);
        *matWorld = tmp;
    }
}

void move_angle(Mat4x4 **matWorld)
{
    Mat4x4 *matMov = NULL;

    if (sfKeyboard_isKeyPressed(sfKeyW))
        matMov = mat4x4_rz(PI/180);
    if (sfKeyboard_isKeyPressed(sfKeyX))
        matMov = mat4x4_rz(-PI/180);
    if (matMov != NULL) {
        *matWorld = mat4x4_MultiplyMat4x4(*matWorld, matMov);
        Mat4x4_destroy(matMov);
    }
}

void move(Mat4x4 **matWorld)
{
    move_player(matWorld);
    move_cam(matWorld);
    move_angle(matWorld);
}
