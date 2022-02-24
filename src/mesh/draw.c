/*
** EPITECH PROJECT, 2022
** draw.c
** File description:
** draw
*/

#include "world.h"

void draw_line(vertex_t vertxs[3], win_t *win)
{
    win->tmp->position = (sfVector2f){vertxs[1].pos[0], vertxs[1].pos[1]};
    sfVertexArray_append(win->array, *win->tmp);
    win->tmp->position = (sfVector2f){vertxs[2].pos[0], vertxs[2].pos[1]};
    sfVertexArray_append(win->array, *win->tmp);
    win->tmp->position = (sfVector2f){vertxs[0].pos[0], vertxs[0].pos[1]};
    sfVertexArray_append(win->array, *win->tmp);
}

void draw_triangle(vertex_t vertxs[3], triangle_t *tri,
win_t *win, world_t *world)
{
    win->tmp->color = center_vertxs(vertxs, tri, world, win);
    for (int i = 0; i < 3; i++) {
        win->tmp->position = (sfVector2f)
        {vertxs[i].pos[0], vertxs[i].pos[1]};
        sfVertexArray_append(win->array, *win->tmp);
    }
    if (win->params->is_outline)
        draw_line(vertxs, win);
}

void fill_pts(vertex_t pts[3], vertex_t *vertxs, triangle_t *tri)
{
    pts[0].pos[0] = vertxs[tri->vertxs[0]].pos[0];
    pts[0].pos[1] = vertxs[tri->vertxs[0]].pos[1];
    pts[0].pos[2] = vertxs[tri->vertxs[0]].pos[2];
    pts[1].pos[0] = vertxs[tri->vertxs[1]].pos[0];
    pts[1].pos[1] = vertxs[tri->vertxs[1]].pos[1];
    pts[1].pos[2] = vertxs[tri->vertxs[1]].pos[2];
    pts[2].pos[0] = vertxs[tri->vertxs[2]].pos[0];
    pts[2].pos[1] = vertxs[tri->vertxs[2]].pos[1];
    pts[2].pos[2] = vertxs[tri->vertxs[2]].pos[2];
}

void draw_meshes(world_t *world, win_t *win)
{
    vertex_t pts[3];
    triangle_t *tri;
    vertex_t *vertxs = project_meshes(world);
    vecsort_t *sortBuffer = sort_vertxs(world, vertxs);

    if (!win->params->pause)
        move_light(world, win);
    if (world->light_source[2] > 0)
        draw_light(world, win);
    for (size_t i = 0; i < world->nb_trig; i++) {
        tri = sortBuffer[i].data;
        fill_pts(pts, vertxs, tri);
        if (pts[0].pos[2] > 0 || pts[1].pos[2] > 0 || pts[2].pos[2] > 0)
            continue;
        if (get_direction(pts) >= 0)
            draw_triangle(pts, tri, win, world);
    }
    sfVertexArray_setPrimitiveType(win->array, win->params->is_outline ?
    sfLines : sfTriangles);
    sfRenderTexture_drawVertexArray(win->r_tex, win->array, 0);
    sfVertexArray_clear(win->array);
    free(vertxs);
}
