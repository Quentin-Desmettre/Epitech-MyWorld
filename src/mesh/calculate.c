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
    float direction = apply_shades(world, tri);
    const float *time = win->params->day ? day_light : night_light;

    for (int i = 0; i < 3; i++) {
        vertxs[i].pos[0] += 1;
        vertxs[i].pos[1] += 1;
        vertxs[i].pos[0] *= 400;
        vertxs[i].pos[1] *= 400;
    }
    color.r *= (direction * time[win->params->hour] + 0.1);
    color.g *= (direction * time[win->params->hour] + 0.1);
    color.b *= (direction * time[win->params->hour] + 0.1);

    color.r *= (direction * time[win->params->hour] + 0.1);
    color.g *= (direction * time[win->params->hour] + 0.1);
    color.b *= (direction * time[win->params->hour] + 0.1);
    return color;
}

float get_direction(vertex_t *pts)
{
    float normal[3];
    float vectors[2][3] = {
    {pts[0].pos[0] - pts[1].pos[0], pts[0].pos[1] -
    pts[1].pos[1], pts[0].pos[2] - pts[1].pos[2]},
    {pts[0].pos[0] - pts[2].pos[0], pts[0].pos[1] -
    pts[2].pos[1], pts[0].pos[2] - pts[2].pos[2]}};
    float cameraDirection[3] = {0, 0, 1};

    normalize(vectors[0]);
    normalize(vectors[1]);
    crossproduct3(normal, vectors[0], vectors[1]);
    normalize(normal);
    return dotproduct3(normal, cameraDirection);
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
    float *tmp = malloc(sizeof(float) * 3);
    vertex_t *vertxs = malloc(sizeof(vertex_t) * world->nb_vertxs);

    for (size_t i = 0; i < world->nb_vertxs; i++) {
        mat4x4_multiplyvector3
        (world->matrix, (float *)world->a_vertxs[i], tmp);
        tmp[0] /= tmp[2];
        tmp[1] /= tmp[2];
        vertxs[i].pos[0] = tmp[0];
        vertxs[i].pos[1] = tmp[1];
        vertxs[i].pos[2] = tmp[2];
    }
    free(tmp);
    return vertxs;
}
