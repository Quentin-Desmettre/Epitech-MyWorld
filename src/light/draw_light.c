/*
** EPITECH PROJECT, 2022
** Workshop3D v4.0
** File description:
** draw
*/

#include "world.h"

void move_light(world_t *world, win_t *win)
{
    mat4x4 *mat_mov = mat4x4_rx(-PI / 120);
    float *tmp = malloc(sizeof(float) * 3);

    if (sfClock_getElapsedTime(world->clock).microseconds / 1000000.0 > 0.25) {
        mat4x4_multiplyvector3(mat_mov, world->light_source, tmp);
        sfClock_restart(world->clock);
        free(world->light_source);
        world->light_source = tmp;
    }
    if (world->light_source[1] < 0) {
        world->light_source[0] = world->light_start[0];
        world->light_source[1] = world->light_start[1];
        world->light_source[2] = world->light_start[2];
        win->params->day = !win->params->day;
    }
    free(mat_mov);
}

void draw_light(world_t *world, win_t *win)
{
    vertex_t *tmp;
    float *vertx = malloc(sizeof(float) * 3);

    mat4x4_multiplyvector3(world->matrix, world->light_source, vertx);
    vertx[0] /= vertx[2];
    vertx[1] /= vertx[2];
    // tmp.pos[0] = vertx[0];
    // tmp.pos[1] = vertx[1];
    // tmp.pos[2] = vertx[2];
    // if (get_direction(&tmp) < 0) {
    //     free(vertx);
    //     return;
    // }
    vertx[0] += 1;
    vertx[1] += 1;
    vertx[0] *= 400;
    vertx[1] *= 400;
    sfCircleShape_setFillColor(win->circle,
    win->params->day ? sfYellow : sfWhite);
    sfCircleShape_setPosition(win->circle, (sfVector2f) {vertx[0], vertx[1]});
    win->draw_circle(win, 1, win->circle);
    free(vertx);
}
