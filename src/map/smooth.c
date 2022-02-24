/*
** EPITECH PROJECT, 2022
** smooth.c
** File description:
** smooth
*/

#include "world.h"

sfBool is_out(size_t max, size_t size, long i, long j)
{
    if (size * i + j >= max && size * i + j > 0)
        return sfTrue;
    return sfFalse;
}

void smooth_point(mesh_t *mesh, size_t size, long line, long col)
{
    vertex_t *vertex = &mesh->vertxs[size * line + col];
    float mid = vertex->pos[1] * 4;
    size_t count = 4;

    for (long i = line - 1; i < line + 1; i++) {
        for (long j = col - 1; j < col + 1; j++) {
            !is_out(mesh->nb_vertxs, size, i, j) ? mid +=
            mesh->vertxs[size * i + j].pos[1], count++ : 0;
        }
    }
    mid /= count;
    vertex->pos[1] = mid;
}

void smooth(mesh_t *mesh, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++)
            smooth_point(mesh, size, i, j);
    }
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - 1; j++)
            change_color(mesh, size, i, j);
    }
}

void smooth_trig(world_t *world, size_t size, long line, long col)
{
    triangle_t *trig = world->a_triangles[(size - 1) * line + col];
    float mid = trig->direction * 3;
    size_t count = 3;

    for (long i = line - 1; i < line + 1; i++) {
        for (long j = col - 1; j < col + 1; j++) {
            !is_out(world->nb_trig, size - 1, i, j) ? mid +=
            world->a_triangles[(size - 1) * i + j]->direction, count++ : 0;
            !is_out(world->nb_trig, size - 1, i, j + (long)(world->nb_trig / 2)) &&
            col < (long)(world->nb_trig / 2) ? mid += world->a_triangles[(size - 1) *
            i + j + (long)(world->nb_trig / 2)]->direction, count++ : 0;
            !is_out(world->nb_trig, size - 1, i, j - (long)(world->nb_trig / 2)) &&
            col >= (long)(world->nb_trig / 2) ? mid += world->a_triangles[(size - 1) *
            i + j - (long)(world->nb_trig / 2)]->direction, count++ : 0;
        }
    }
    mid /= count;
    trig->direction = mid;

}

void smooth_shadow(world_t *world, win_t *win)
{
    float direction;
    size_t size = win->map_size;
    const float *time = win->params->day ? day_light : night_light;

    for (size_t i = 0; i < world->nb_trig; i++) {
        direction = apply_shades(world, world->a_triangles[i]) * time[win->params->hour] + 0.1;
        world->a_triangles[i]->direction = direction;
    }
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - 1; j++) {
            smooth_trig(world, size, i, j);
            smooth_trig(world, size, i, j);
            smooth_trig(world, size, i, j + world->nb_trig / 2);
            smooth_trig(world, size, i, j + world->nb_trig / 2);
        }
    }
}
