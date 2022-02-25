/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "world.h"

void app_point(float x, float y, win_t *win)
{
    win->tmp->position = (sfVector2f){x, y};
    sfVertexArray_append(win->array, *win->tmp);
}

void where_minimap(world_t *world, win_t *win, long long size)
{
    float nb = height / (float)(size);
    int x = (int)(round(sfMouse_getPositionRenderWindow(win->window).x / nb));
    int y = (int)(round(sfMouse_getPositionRenderWindow(win->window).y / nb));
    float xx;
    float yy;
    if (x < 0 || y < 0 || x > size || y > size)
        return;
    xx = world->a_vertxs[x * (size + 1) + y]->pos[0] / 1.5;
    yy = world->a_vertxs[x * (size + 1) + y]->pos[2] / 1.5;
    win->tmp->color = sfWhite;
    app_point((xx - world->s_br) * nb, (yy + world->s_br) * nb, win);
    app_point((xx - world->s_br) * nb, (yy - world->s_br) * nb, win);
    app_point((xx + world->s_br) * nb, (yy - world->s_br) * nb, win);
    app_point((xx + world->s_br) * nb, (yy + world->s_br) * nb, win);
    app_point((xx - world->s_br) * nb, (yy + world->s_br) * nb, win);
    sfVertexArray_setPrimitiveType(win->array, sfLinesStrip);
    sfRenderWindow_drawVertexArray(win->window, win->array, 0);
    sfVertexArray_clear(win->array);
    average_d_br(world, win, sfMouse_getPositionRenderWindow(win->window));
}

void add_color(int i, win_t *win, world_t *world, const float *time)
{
    float direction = world->a_triangles[i]->direction;
    win->tmp->color = world->a_triangles[i]->color;
    win->tmp->color.r *= direction;
    win->tmp->color.g *= direction;
    win->tmp->color.b *= direction;
}

void create_minimap(world_t *world, win_t *win, long long size)
{
    const float *time = win->params->day ? day_light : night_light;
    float nb = height / (float)(size);
    sfBool day = win->params->day;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            add_color(i * size + j, win, world, time);
            app_point(nb * i, nb * (size - j - 1), win);
            app_point(nb * (i + 1), nb * (size - j - 1), win);
            app_point(nb * i, nb * (size - j), win);
            add_color(i * size + j + size * size, win, world, time);
            app_point(nb * (i + 1), nb * (size - j), win);
            app_point(nb * (i + 1), nb * (size - j - 1), win);
            app_point(nb * i, nb * (size - j), win);
        }
    }
    sfVertexArray_setPrimitiveType(win->array, sfTriangles);
    sfRenderWindow_drawVertexArray(win->window, win->array, 0);
    sfVertexArray_clear(win->array);
    where_minimap(world, win, size);
}
