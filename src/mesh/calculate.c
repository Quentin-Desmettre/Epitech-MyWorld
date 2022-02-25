/*
** EPITECH PROJECT, 2022
** calculate.c
** File description:
** calculate
*/

#include "world.h"

sfColor center_vertxs(vertex_t *vertxs, triangle_t *tri,
world_t *world, win_t *win)
{
    sfColor color = tri->color;
    float direction = tri->direction;

    for (int i = 0; i < 3; i++) {
        vertxs[i].pos[0] += 1;
        vertxs[i].pos[1] += 1;
        vertxs[i].pos[0] *= 400;
        vertxs[i].pos[1] *= 400;
    }
    color.r *= direction;
    color.g *= direction;
    color.b *= direction;
    return color;
}

float get_direction(vertex_t *pts)
{
    float vectors[2][2] = {
    {pts[0].pos[0] - pts[1].pos[0], pts[0].pos[1] - pts[1].pos[1]},
    {pts[0].pos[0] - pts[2].pos[0], pts[0].pos[1] - pts[2].pos[1]}};

    return vectors[0][0] * vectors[1][1] - vectors[0][1] * vectors[1][0];
}

void for_content(world_t *world, vertex_t *vertxs, int i)
{
    int *pts = world->a_triangles[i]->vertxs;
    float v_mid[3] = {
        vertxs[pts[0]].pos[0] + vertxs[pts[1]].pos[0] + vertxs[pts[0]].pos[2],
        vertxs[pts[0]].pos[1] + vertxs[pts[1]].pos[1] + vertxs[pts[1]].pos[2],
        vertxs[pts[0]].pos[2] + vertxs[pts[1]].pos[2] + vertxs[pts[2]].pos[2]
    };

    world->sortBuffer[i].id = -(v_mid[0] * v_mid[0] + v_mid[1] *
    v_mid[1] + v_mid[2] * v_mid[2]);
    world->sortBuffer[i].data = world->a_triangles[i];
}

vecsort_t *sort_vertxs(world_t *world, vertex_t *vertxs)
{
    for (size_t i = 0; i < world->nb_trig; i++)
        for_content(world, vertxs, i);
    radix_sort(world->sortBuffer,
    (size_t [2]){sizeof(vecsort_t), world->nb_trig},
    (size_t)&((vecsort_t *)0)->id, world->sortBuffer2);
    return world->sortBuffer;
}

vertex_t *project_meshes(world_t *world)
{
    size_t i = -1;
    vertex_t *vertxs = malloc(sizeof(vertex_t) * world->nb_vertxs);

    while ((i += 1) < world->nb_vertxs) {
        mat4x4_multiplyvector3
        (world->matrix, world->a_vertxs[i]->pos, vertxs[i].pos);
        vertxs[i].pos[0] /= vertxs[i].pos[2];
        vertxs[i].pos[1] /= vertxs[i].pos[2];
    }
    return vertxs;
}
