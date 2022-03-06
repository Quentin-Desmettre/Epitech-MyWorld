/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** actions.c
*/

#include "menus.h"

void save_game(void *w)
{
    window_t *win = w;
    game_t *g = win->menus[EDIT_MAP];

    save_map(g, MAP_STRING, MAP_SIZE);
}

void add_hour(void *win)
{
    window_t *w = win;
    game_t *ga = w->menus[EDIT_MAP];

    rota_right(ga->world, ga->win);
}

void sub_hour(void *win)
{
    window_t *w = win;
    game_t *ga = w->menus[EDIT_MAP];

    rota_left(ga->world, ga->win);
}

void pause_game(void *win)
{
    window_t *w = win;
    game_t *ga = w->menus[EDIT_MAP];

    ga->win->params->pause = !ga->win->params->pause;
}
