/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** release.c
*/

#include "menus.h"

void remove_level(map_select_t *m, int level)
{
    if (level == 3)
        m->background = m->background;
}

map_entry_t *entry_at_list(list_t *l, int index)
{
    for (int i = 0; i < index; i++)
        l = l->next;
    return l->data;
}

void load_map(char const *map, window_t *win)
{
    unsigned size = map_size(map);

    win->menus[EDIT_MAP] = create_game(size,
    (sfVector2f){win->mode.width, win->mode.height});
    read_map(win->menus[EDIT_MAP], map);
    set_next_win_state(win, EDIT_MAP);
    update_color(((game_t *)(win->menus[EDIT_MAP]))->world);
}

void recolor_buttons(map_select_t *m, sfVector2f pos)
{
    m->primary = entry_at(m, pos);
    for (int i = 1; i < 3; i++) {
        sfSprite_setColor(m->buttons[i]->sprite,
        m->primary >= 0 ? sfWhite : SEMI_COLOR);
        sfText_setFillColor(m->buttons[i]->text,
        m->primary >= 0 ? sfWhite : SEMI_COLOR);
    }
}

void manage_release(map_select_t *m, sfEvent ev, window_t *win)
{
    int but;
    sfVector2f pos = {ev.mouseButton.x, ev.mouseButton.y};

    for (int i = 0; i < 3; i++)
        press_button(m->buttons[i], false);
    ev.mouseButton.x = pos.x;
    ev.mouseButton.y = pos.y;
    but = button_at(m->buttons, 3, ev);
    if (but < 0)
        recolor_buttons(m, pos);
    else {
        if (but == 0)
            set_next_win_state(win, HOME);
        if (but == 1 && m->primary >= 0)
            remove_level(m, m->primary);
        if (but == 2 && m->primary >= 0)
            load_map(sfText_getString(entry_at_list
            (m->maps, m->primary)->level_name), win);
    }
}
