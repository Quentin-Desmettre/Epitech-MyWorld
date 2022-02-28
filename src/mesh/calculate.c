/*
** EPITECH PROJECT, 2022
** calculate.c
** File description:
** calculate
*/

#include "world.h"

sfColor center_vertxs(vertex_t *vertxs, triangle_t *tri)
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
    float vectors[4] = {pts[0].pos[0] - pts[1].pos[0], pts[0].pos[1] - pts[1]
    .pos[1], pts[0].pos[0] - pts[2].pos[0], pts[0].pos[1] - pts[2].pos[1]};

    return vectors[0] * vectors[3] - vectors[1] * vectors[2];
}

// void for_content(world_t *world, int i)
// {
//     vertex_t *pt0 = world->a_triangles[i].ptrs[0];
//     vertex_t *pt1 = world->a_triangles[i].ptrs[1];
//     vertex_t *pt2 = world->a_triangles[i].ptrs[2];
//     float v_mid[3] = {pt0->pos[0] + pt1->pos[0] + pt2->pos[0], pt0->pos[1] +
//     pt1->pos[1] + pt2->pos[1], pt0->pos[2] + pt1->pos[2] + pt2->pos[2]};

//     world->sortBuffer[i].id = -(v_mid[0] * v_mid[0] + v_mid[1] *
//     v_mid[1] + v_mid[2] * v_mid[2]);
//     world->sortBuffer[i].data = &world->a_triangles[i];
// }

void for_content(world_t *world, int i)
{
    vertex_t **pts = world->a_triangles[i].ptrs;
    float v_mid[3] = {
    pts[0]->pos[0] + pts[1]->pos[0] + pts[2]->pos[0],
    pts[0]->pos[1] + pts[1]->pos[1] + pts[2]->pos[1],
    pts[0]->pos[2] + pts[1]->pos[2] + pts[2]->pos[2]};

    world->sortBuffer[i].id = -(v_mid[0] * v_mid[0] + v_mid[1] *
    v_mid[1] + v_mid[2] * v_mid[2]);
    world->sortBuffer[i].data = &world->a_triangles[i];
}

void sort_vertxs(world_t *world)
{
    for (size_t i = 0; i < world->nb_trig; i++)
        for_content(world, i);
    radix_sort(world->sortBuffer, (size_t [2]){sizeof(vecsort_t),
    world->nb_trig}, (size_t)&((vecsort_t *)0)->id, world->sortBuffer2);
}

void project_meshes(world_t *world)
{
    size_t i = -1;

    while ((i += 1) < world->nb_vertxs) {
        mat4x4_multiplyvector3
        (world->matrix, world->a_vertxs[i].pos, world->projected[i].pos);
        world->projected[i].pos[0] /= world->projected[i].pos[2];
        world->projected[i].pos[1] /= world->projected[i].pos[2];
    }
}
