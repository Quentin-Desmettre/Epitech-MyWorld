/*
** EPITECH PROJECT, 2022
** win_draw.c
** File description:
** win_draw
*/

#include "world.h"

void draw_circle(win_t *win, size_t nb, ...)
{
    va_list list_arg;

    va_start(list_arg, nb);
    for (size_t i = 0; i < nb; i++) {
        sfRenderWindow_drawCircleShape(win->window
        , va_arg(list_arg, sfCircleShape *), 0);
    }
}

void draw_shape(win_t *win, size_t nb, ...)
{
    va_list list_arg;

    va_start(list_arg, nb);
    for (size_t i = 0; i < nb; i++) {
        sfRenderWindow_drawConvexShape(win->window
        , va_arg(list_arg, sfConvexShape *), 0);
    }
}

void display(win_t *win)
{
    sfRenderWindow_display(win->window);
    sfRenderWindow_clear(win->window, sfBlack);
}
