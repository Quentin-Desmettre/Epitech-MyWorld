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
        sfRenderTexture_drawCircleShape(win->r_tex
        , va_arg(list_arg, sfCircleShape *), 0);
    }
}

void draw_shape(win_t *win, size_t nb, ...)
{
    va_list list_arg;

    va_start(list_arg, nb);
    for (size_t i = 0; i < nb; i++) {
        sfRenderTexture_drawConvexShape(win->r_tex
        , va_arg(list_arg, sfConvexShape *), 0);
    }
}

void display(win_t *win)
{
    sfRenderTexture_display(win->r_tex);
    sfRenderTexture_clear(win->r_tex, sfBlack);
}
