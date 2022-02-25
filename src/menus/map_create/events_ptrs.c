/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** events_ptrs.c
*/

#include "menus.h"

void increase_size(void *w)
{
    window_t *win = w;
}

void decrease_size(void *w)
{
    window_t *win = w;
}

void launch_size(void *w)
{
    window_t *win = w;
}

void mc_go_back(void *w)
{
    window_t *win = w;
    set_next_win_state(win, HOME);
}

void mc_event(window_t *win, sfEvent ev)
{
    map_create_t *mc = win->menus[3];

    line_edit_event(mc->name, ev);
}
