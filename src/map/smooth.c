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

void smooth_trig(void *param)
{
    tmp_t *tmp = param;
    world_t *world = tmp->world;
    size_t size = tmp->size;
    long line = tmp->line;
    long col = tmp->col;
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

void for_loop(void *param)
{
    tmp_t *tmp = param;

    for (size_t i = tmp->start; i < tmp->end; i++) {
        for (size_t j = 0; j < tmp->size - 1; j++) {
            tmp->line = i;
            tmp->col = j;
            smooth_trig(tmp);
            tmp->col = j + tmp->world->nb_trig / 2;
            smooth_trig(tmp);
        }
    }
}

void smooth_shadow(world_t *world, win_t *win)
{
    tmp_t *tmp = malloc(sizeof(tmp_t));
    tmp_t *tmp2 = malloc(sizeof(tmp_t));
    sfThread *thread1 = sfThread_create(for_loop, tmp);
    sfThread *thread2 = sfThread_create(for_loop, tmp2);
    float direction;
    size_t size = win->map_size;
    const float *time = win->params->day ? day_light : night_light;

    tmp->world = world;
    tmp->size = size;
    tmp2->world = world;
    tmp2->size = size;
    for (size_t i = 0; i < world->nb_trig; i++) {
        direction = apply_shades(world, world->a_triangles[i]) *
        (win->params->day ? 0.8 : 0.2) + 0.1;
        world->a_triangles[i]->direction = direction;
    }
    tmp->start = 0;
    tmp->end = (size - 1) / 2;
    tmp2->start = (size - 1) / 2;
    tmp2->end = size - 1;
    sfThread_launch(thread1);
    sfThread_launch(thread2);
    sfThread_wait(thread1);
    sfThread_wait(thread2);
    sfThread_destroy(thread1);
    sfThread_destroy(thread2);
    free(tmp2);
    free(tmp);
}
