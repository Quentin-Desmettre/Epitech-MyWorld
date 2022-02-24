/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** init_window.c
*/

#include "menus.h"

void switch_color_dir(window_t *win, int *dir)
{
    win->state = win->next_state;
    *dir = -1;
    if (win->state == EXIT)
        sfRenderWindow_close(win->win);
}

void reset_lum(window_t *win, int *dir, sfColor *lum)
{
    *dir = 1;
    win->is_transition = false;
    *lum = (sfColor){255, 255, 255, 255};
}

void update_lum(sfColor *lum, int *fac)
{
    lum->a -= *fac;
    lum->b -= *fac;
    lum->r -= *fac;
    lum->g -= *fac;
}

void update_transition(window_t *win, sfSprite *s)
{
    static bool dir = 1;
    int fac = dir * 24;
    static sfColor lum = {255, 255, 255, 255};

    if (win->is_transition &&
    sfClock_getElapsedTime(win->lum_clock).microseconds > 33333) {
        if (lum.a == 39)
            switch_color_dir(win, &dir);
        update_lum(&lum, &fac);
        sfSprite_setColor(s, lum);
        if (dir == -1 && lum.a == 255)
            reset_lum(win, &dir, &lum);
        sfClock_restart(win->lum_clock);
    }
    sfSprite_setColor(s, lum);
}

window_t *win_create(void)
{
    window_t *win = malloc(sizeof(window_t));
    const sfTexture* (*dr[6])(void *) = {
        &draw_main_menu, NULL, &draw_settings, NULL, NULL, NULL
    };
    void (*ev[6])(window_t *, sfEvent) = {
        &main_menu_event, NULL, &settings_ev, NULL, NULL, NULL
    };

    win->state = HOME;
    win->next_state = HOME;
    win->is_transition = 0;
    win->win = sfRenderWindow_create(
        (sfVideoMode){800, 600, 32}, "My world", sfClose, NULL);
    win->menus[0] = init_main_menu(global_texture(), (sfVector2f){800, 600});
    win->mode = (sfVideoMode){800, 600, 32};
    win->menus[2] = init_settings(win);
    for (int i = 0; i < 6; i++) {
        win->draw[i] = dr[i];
        win->event[i] = ev[i];
    }
    win->lum_clock = sfClock_create();
    return win;
}
