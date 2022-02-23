/*
** EPITECH PROJECT, 2022
** params.c
** File description:
** params
*/

#include "world.h"

void params(win_t *win)
{
    if (win->event.type == sfEvtKeyReleased &&
    win->event.key.code == sfKeyF3) {
        win->params->is_fill = win->params->is_fill == 0;
        win->params->is_outline = win->params->is_outline == 0;
    }
}
