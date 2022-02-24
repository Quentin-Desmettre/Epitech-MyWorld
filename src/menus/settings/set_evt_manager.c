/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** settings_events.c
*/

#include "menus.h"

sfFloatRect bounds(sfSprite *s)
{
    return sfSprite_getGlobalBounds(s);
}

int get_set_button_at(settings_t *se, sfEvent *ev)
{
    sfFloatRect all_bounds[9] = {bounds(se->back->sprite),
    bounds(se->full_screen->box), bounds(se->vsync->box),
    bounds(se->res_button->sprite), bounds(se->framerate_button->sprite),
    bounds(se->sfx_minus->sprite), bounds(se->sfx_plus->sprite),
    bounds(se->music_minus->sprite), bounds(se->music_plus->sprite)
    };
    sfVector2f pos = ev->type == sfEvtMouseMoved ?
    (sfVector2f){ev->mouseMove.x, ev->mouseMove.y} :
    (sfVector2f){ev->mouseButton.x, ev->mouseButton.y};

    for (int i = 0; i < 9; i++)
        if (sfFloatRect_contains(&all_bounds[i],
        pos.x, pos.y))
            return i;
    return -1;
}

void manage_settings_hover(sfEvent *ev, window_t *win)
{
    settings_t *se = win->menus[2];
    button_t *buttons[9] = {se->back, NULL, NULL, se->res_button,
    se->framerate_button, se->sfx_minus, se->sfx_plus,
    se->music_minus, se->music_plus};
    int tmp = get_set_button_at(se, ev);

    if (tmp < 0 || buttons[tmp] == NULL ||
    (tmp == 3 && se->full_screen->is_checked)) {
        reset_set_buttons(se);
        return;
    }
    if (sfMouse_isButtonPressed(sfMouseLeft))
        press_button(buttons[tmp], 1);
    else
        hover_button(buttons[tmp], 1);
}

void manage_settings_press(sfEvent *ev, window_t *win)
{
    settings_t *se = win->menus[2];
    button_t *buttons[9] = {se->back, NULL, NULL, se->res_button,
    se->framerate_button, se->sfx_minus, se->sfx_plus,
    se->music_minus, se->music_plus};
    int tmp = get_set_button_at(se, ev);
    void (*actions[9])(settings_t *, window_t *) = {
        NULL, NULL, NULL,
        NULL, NULL, sfx_minus,
        sfx_plus, music_minus, music_plus
    };
    if (tmp < 0 || buttons[tmp] == NULL || (tmp == 3 &&
    se->full_screen->is_checked) || (tmp <= 4 && ev->type == sfEvtResized)) {
        reset_set_buttons(se);
        return;
    }
    if (actions[tmp])
        actions[tmp](se, win);
    press_button(buttons[tmp], 1);
    if (ev->type != sfEvtResized || tmp <= 4)
        sfClock_restart(se->repeat_clock);
}

void manage_settings_release(sfEvent *ev, window_t *win)
{
    settings_t *se = win->menus[2];
    int tmp = get_set_button_at(se, ev);
    void (*actions[9])(settings_t *, window_t *) = {
        go_back, update_full_screen, update_vsync,
        update_res, update_framerate, NULL,
        NULL, NULL, NULL
    };

    reset_set_buttons(se);
    if (tmp < 0 ||
    (tmp == 3 && se->full_screen->is_checked))
        return;
    if (actions[tmp])
        actions[tmp](se, win);
    update_all_texts(se);
}
