/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "world.h"

void my_append_point(sfVector2f pos, win_t *win)
{
    win->tmp->position = pos;
    sfVertexArray_append(win->array, *win->tmp);
}
void where_minimap(world_t *world, win_t *win, long long size)
{
    float nb = 800.0 / (float)(size);
    int x = (int)(round(sfMouse_getPositionRenderWindow(win->window).x / nb));
    int y = (int)(round(sfMouse_getPositionRenderWindow(win->window).y / nb));
    float xx;
    float yy;
    if (x < 0 || y < 0 || x > size || y > size)
        return;
    xx = world->a_vertxs[x * (size + 1) + y]->pos[0] / 1.5;
    yy = world->a_vertxs[x * (size + 1) + y]->pos[2] / 1.5;
    win->tmp->color = sfWhite;
    my_append_point((sfVector2f){(xx - world->size_brush) * nb
    , (yy + world->size_brush) * nb}, win);
    my_append_point((sfVector2f){(xx - world->size_brush) * nb
    , (yy - world->size_brush) * nb}, win);
    my_append_point((sfVector2f){(xx + world->size_brush) * nb
    , (yy - world->size_brush) * nb}, win);
    my_append_point((sfVector2f){(xx + world->size_brush) * nb
    , (yy + world->size_brush) * nb}, win);
    my_append_point((sfVector2f){(xx - world->size_brush) * nb
    , (yy + world->size_brush) * nb}, win);
    sfVertexArray_setPrimitiveType(win->array, sfLinesStrip);
    sfRenderWindow_drawVertexArray(win->window, win->array, 0);
    sfVertexArray_clear(win->array);
}

void get_color_mini(win_t *win, float direction, const float *time)
{
    win->tmp->color.r *= (direction * time[win->params->hour] + 0.1);
    win->tmp->color.g *= (direction * time[win->params->hour] + 0.1);
    win->tmp->color.b *= (direction * time[win->params->hour] + 0.1);
}

void create_minimap(world_t *world, win_t *win, long long size)
{
    const float *time = win->params->day ? day_light : night_light;
    float nb = 800.0 / (float)(size - 1);
    sfBool day = win->params->day;
    float direction = 0;
    sfVertexArray_clear(win->array);
    size--;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            direction = apply_shades(world, world->a_triangles[i * size + j]);
            win->tmp->color = world->a_triangles[i * size + j]->color;
            get_color_mini(win, direction, time);
            my_append_point((sfVector2f){nb * i, nb * (size - j - 1)}, win);
            my_append_point((sfVector2f){nb * (i + 1), nb * (size - j - 1)}, win);
            my_append_point((sfVector2f){nb * i, nb * (size - j)}, win);
            direction = apply_shades(world, world->a_triangles[i * size + j + size * size]);
            win->tmp->color = world->a_triangles[i * size + j + size * size]->color;
            get_color_mini(win, direction, time);
            my_append_point((sfVector2f){nb * (i + 1), nb * (size - j)}, win);
            my_append_point((sfVector2f){nb * (i + 1), nb * (size - j - 1)}, win);
            my_append_point((sfVector2f){nb * i, nb * (size - j)}, win);
        }
    }
    sfVertexArray_setPrimitiveType(win->array, sfTriangles);
    sfRenderWindow_drawVertexArray(win->window, win->array, 0);
    sfVertexArray_clear(win->array);
    where_minimap(world, win, size);
}