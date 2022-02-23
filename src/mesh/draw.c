/*
** EPITECH PROJECT, 2022
** draw.c
** File description:
** draw
*/

#include "world.h"

void draw_line(vertex_t vertxs[3], win_t *win, sfColor color, sfBool is_selected)
{
    sfRenderWindow_drawVertexArray(win->window, win->array, 0);
    sfVertexArray_clear(win->array);
    win->tmp->color = is_selected ? sfWhite : color;
    sfVertexArray_setPrimitiveType(win->array, sfLines);
    for (int i = 0; i < 3; i++) {
        win->tmp->position = (sfVector2f){vertxs[i].pos[0], vertxs[i].pos[1]};
        sfVertexArray_append(win->array, *win->tmp);
    }
    sfRenderWindow_drawVertexArray(win->window, win->array, 0);
    sfVertexArray_setPrimitiveType(win->array, sfTriangles);
    sfVertexArray_clear(win->array);
}

void draw_triangle(vertex_t vertxs[3], sfColor color, win_t *win
, sfBool is_selected, float direction)
{
    center_vertxs(vertxs, &color, direction, win->params->day);
    win->tmp->color = color;
    if (!win->params->is_outline) {
        for (int i = 0; i < 3; i++) {
            win->tmp->position = (sfVector2f)
            {vertxs[i].pos[0], vertxs[i].pos[1]};
            sfVertexArray_append(win->array, *win->tmp);
        }
    }
    if (is_selected || win->params->is_outline)
        draw_line(vertxs, win, color, is_selected);
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
    // clock_t t;
    // t = clock();
    vertex_t *vertxs = project_meshes(world);
    VecSort_t *sortBuffer = sort_vertxs(world, vertxs);

    move_light(world, win);
    draw_light(world, win);
    for (size_t i = 0; i < world->nb_trig; i++) {
        tri = sortBuffer[i].data;
        fill_pts(pts, vertxs, tri);
        if (pts[0].pos[2] > 0 || pts[1].pos[2] > 0 || pts[2].pos[2] > 0)
            continue;
        if (get_direction(pts) >= 0) {
            draw_triangle(pts, tri->color, win, !tri->mesh_ptr ? sfFalse :
            ((mesh_t *)tri->mesh_ptr)->is_selected, apply_shades(world, tri));
        }
    }
    sfRenderWindow_drawVertexArray(win->window, win->array, 0);
    sfVertexArray_clear(win->array);
    // t = clock() - t;
    // double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    // printf("fun() took %f seconds to execute \n", time_taken);
    free(vertxs);
}
