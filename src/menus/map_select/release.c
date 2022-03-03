/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** release.c
*/

#include "menus.h"

void remove_level(map_select_t *m, int level)
{
}

map_entry_t *entry_at_list(list_t *l, int index)
{
    for (int i = 0; i < index; i++)
        l = l->next;
    return l->data;
}

unsigned map_size(char const *map)
{
    char *str = str_concat(2, "./map/", map);
    int fd = open(str, O_RDONLY);
    unsigned size = 64;

    if (fd >= 0)
        read(fd, &size, sizeof(unsigned));
    free(str);
    close(fd);
    return size;
}

void load_map(char const *map, window_t *win)
{
    unsigned size = map_size(map);

    size--;
    win->menus[EDIT_MAP] = create_game(size,
    (sfVector2f){win->mode.width, win->mode.height});
    read_map(win->menus[EDIT_MAP], map);
    set_next_win_state(win, EDIT_MAP);
    update_color(((game_t *)(win->menus[EDIT_MAP]))->world);
}

void manage_release(map_select_t *m, sfEvent ev, window_t *win)
{
    int but;
    sfVector2f pos = {ev.mouseButton.x, ev.mouseButton.y};

    for (int i = 0; i < 3; i++)
        press_button(m->buttons[i], false);
    ev.type = sfEvtMouseButtonReleased;
    ev.mouseButton.x = pos.x;
    ev.mouseButton.y = pos.y;
    but = button_at(m->buttons, 3, ev);
    if (but < 0)
        m->primary = entry_at(m, pos);
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
