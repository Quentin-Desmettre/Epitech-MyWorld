/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "world.h"

void create_minimap(world_t *world, win_t *win, long long size)
{
    const float *time = win->params->day ? day_light : night_light;
    float nb = 800.0 / (float)(size - 1);
    sfBool day = win->params->day;
    float direction = 0;
    size = size - 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            direction = apply_shades(world, world->a_triangles[i * size + j]);
            win->tmp->color = world->a_triangles[i * size + j]->color;
            win->tmp->color.r *= (direction * time[win->params->hour] + 0.1);
            win->tmp->color.g *= (direction * time[win->params->hour] + 0.1);
            win->tmp->color.b *= (direction * time[win->params->hour] + 0.1);
            win->tmp->position = (sfVector2f){nb * i, nb * (size - j)};
            sfVertexArray_append(win->array, *win->tmp);
            win->tmp->position = (sfVector2f){nb * (i + 1), nb * (size - j)};
            sfVertexArray_append(win->array, *win->tmp);
            win->tmp->position = (sfVector2f){nb * i, nb * (size - j + 1)};
            sfVertexArray_append(win->array, *win->tmp);
            direction = apply_shades(world, world->a_triangles[i * size + j + size * size]);
            win->tmp->color = world->a_triangles[i * size + j + size * size]->color;
            win->tmp->color.r *= (direction * time[win->params->hour] + 0.1);
            win->tmp->color.g *= (direction * time[win->params->hour] + 0.1);
            win->tmp->color.b *= (direction * time[win->params->hour] + 0.1);
            win->tmp->position = (sfVector2f){nb * (i + 1), nb * (size - j + 1)};
            sfVertexArray_append(win->array, *win->tmp);
            win->tmp->position = (sfVector2f){nb * (i + 1), nb * (size - j)};
            sfVertexArray_append(win->array, *win->tmp);
            win->tmp->position = (sfVector2f){nb * i, nb * (size - j + 1)};
            sfVertexArray_append(win->array, *win->tmp);
        }
    }
    sfVertexArray_setPrimitiveType(win->array, sfTriangles);
    sfRenderWindow_drawVertexArray(win->window, win->array, 0);
    sfVertexArray_clear(win->array);
}