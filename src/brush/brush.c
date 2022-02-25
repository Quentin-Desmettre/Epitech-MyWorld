/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "world.h"

void up_br(world_t *world, win_t *win, sfVector2i pos)
{
    float nb = height / (float)(win->map_size);
    int x = (int)(round(sfMouse_getPositionRenderWindow(win->window).x / nb));
    int y = (int)(round(sfMouse_getPositionRenderWindow(win->window).y / nb));
    if (x < 0 || y < 0 || x > (int)win->map_size || y > (int)win->map_size)
        return;
    for (int i = x - world->s_br; i < x + world->s_br; i++) {
        if (i < 0 || i >= (int)win->map_size)
            continue;
        for (int j = y - world->s_br; j < y + world->s_br; j++) {
            !((win->map_size - j) < 0 || (int)(win->map_size - j) >=
            (int)(win->map_size) || world->a_vertxs
            [i * (win->map_size) + (win->map_size - j)]->pos[1] > 40) ?
            world->a_vertxs[i * (win->map_size) + (win->map_size - j)]->
            pos[1] += 1 : 0;
        }
    }
}

void down_br(world_t *world, win_t *win, sfVector2i pos)
{
    float nb = height / (float)(win->map_size);
    int x = (int)(round(sfMouse_getPositionRenderWindow(win->window).x / nb));
    int y = (int)(round(sfMouse_getPositionRenderWindow(win->window).y / nb));
    if (x < 0 || y < 0 || x > (int)win->map_size || y > (int)win->map_size)
        return;
    for (int i = x - world->s_br; i < x + world->s_br; i++) {
        if (i < 0 || i >= (int)win->map_size)
            continue;
        for (int j = y - world->s_br; j < y + world->s_br; j++) {
            !((win->map_size - j) < 0 || (int)(win->map_size - j) >=
            (int)(win->map_size) || world->a_vertxs
            [i * (win->map_size) + (win->map_size - j)]->pos[1] < -10) ?
            world->a_vertxs[i * (win->map_size) + (win->map_size - j)]->
            pos[1] += 1 : 0;
        }
    }
}