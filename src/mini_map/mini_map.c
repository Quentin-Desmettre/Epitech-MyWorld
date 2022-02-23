/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "world.h"

void create_minimap(world_t *world, win_t *win, long long size)
{
    float nb = 800 / (size - 1);
    long long tmp = 0;
    sfBool day = win->params->day;
    float direction = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            direction = apply_shades(world, world->a_triangles[tmp]);
            win->tmp->color = world->a_triangles[tmp]->color;
            win->tmp->color.r *= (direction * (day ? SUN : MOON) + 0.1);
            win->tmp->color.g *= (direction * (day ? SUN : MOON) + 0.1);
            win->tmp->color.b *= (direction * (day ? SUN : MOON) + 0.1);
            win->tmp->position = (sfVector2f)(sfVector2f){nb * i, nb * j};
            sfVertexArray_append(win->array, *win->tmp);
            win->tmp->position = (sfVector2f)(sfVector2f){nb * (i + 1), nb * j};
            sfVertexArray_append(win->array, *win->tmp);
            win->tmp->position = (sfVector2f)(sfVector2f){nb * i, nb * (j + 1)};
            sfVertexArray_append(win->array, *win->tmp);
            sfVertexArray_setPrimitiveType(win->array, sfTriangles);
            tmp++;
        }
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            direction = apply_shades(world, world->a_triangles[tmp]);
            win->tmp->color = world->a_triangles[tmp]->color;
            win->tmp->color.r *= (direction * (day ? SUN : MOON) + 0.1);
            win->tmp->color.g *= (direction * (day ? SUN : MOON) + 0.1);
            win->tmp->color.b *= (direction * (day ? SUN : MOON) + 0.1);
            win->tmp->position = (sfVector2f)(sfVector2f){nb * (i + 1), nb * (j + 1)};
            sfVertexArray_append(win->array, *win->tmp);
            win->tmp->position = (sfVector2f)(sfVector2f){nb * (i + 1), nb * j};
            sfVertexArray_append(win->array, *win->tmp);
            win->tmp->position = (sfVector2f)(sfVector2f){nb * i, nb * (j + 1)};
            sfVertexArray_append(win->array, *win->tmp);
            sfVertexArray_setPrimitiveType(win->array, sfTriangles);
            tmp++;
        }
    }
    sfRenderWindow_drawVertexArray(win->window, win->array, 0);
    sfVertexArray_clear(win->array);
}