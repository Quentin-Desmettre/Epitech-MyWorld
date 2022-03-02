/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** events.c
*/

#include "menus.h"

sfFloatRect get_entry_rect(map_entry_t *m, sfVector2f pos)
{
    sfSprite *s = draw_entry(m);
    sfFloatRect rect;

    sfSprite_setPosition(s, pos);
    rect = sfSprite_getGlobalBounds(s);
    sfSprite_destroy(s);
    return rect;
}

static int entry_at(map_select_t *m, sfVector2f m_pos)
{
    list_t *start = m->maps;
    sfVector2f pos = {m->size.x * 0.2, m->size.y * 0.2 - m->x_start};
    sfSprite *s;
    sfFloatRect rect;
    int i = 0;

    if (!start)
        return -1;
    do {
        rect = get_entry_rect(start->data, pos);
        if (sfFloatRect_contains(&rect,
        m_pos.x + rect.width * 0.15, m_pos.y + rect.height))
            return i;
        pos.y += m->size.y * ENTRY_Y_SPAN * ENTRY_SPACING;
        start = start->next;
        i++;
    } while (start != m->maps);
    return -1;
}

static inline void manage_move(map_select_t *m, sfEvent ev)
{
    sfVector2f pos = {ev.mouseMove.x, ev.mouseMove.y};
    check_button_move(m->buttons, 3 - (m->primary < 0 ? 1 : 0), ev);
    ev.type = sfEvtMouseButtonReleased;
    ev.mouseButton.x = pos.x;
    ev.mouseButton.y = pos.y;
    if (button_at(m->buttons, 3, ev) < 0)
        m->secondary = entry_at(m, pos);
    else
        m->secondary = -1;
}

static inline void manage_press(map_select_t *m, sfEvent ev)
{
    check_button_press(m->buttons, 3 - (m->primary < 0 ? 1 : 0), ev);
}

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

    printf("size: %d\n", size);
    win->menus[EDIT_MAP] = create_game(size,
    (sfVector2f){win->mode.width, win->mode.height});
    read_map(win->menus[EDIT_MAP], map);
    set_next_win_state(win, EDIT_MAP);
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
        if (but == 2 && m->primary >= 0) {
            load_map(sfText_getString(entry_at_list(m->maps, m->primary)->level_name), win);
        }
    }
}

static inline void manage_scroll(map_select_t *m, sfEvent ev)
{
    m->x_start -= ev.mouseWheelScroll.delta * 20;
    if (m->x_start < 0)
        m->x_start = 0;
}

void map_select_events(window_t *w, sfEvent ev)
{
    map_select_t *m = w->menus[MAP_SELECT];

    if (ev.type == sfEvtMouseMoved)
        manage_move(m, ev);
    if (ev.type == sfEvtMouseButtonPressed)
        manage_press(m, ev);
    if (ev.type == sfEvtMouseButtonReleased)
        manage_release(m, ev, w);
    if (ev.type == sfEvtMouseWheelScrolled)
        manage_scroll(m, ev);
}
