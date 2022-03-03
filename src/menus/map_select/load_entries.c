/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** load_entries.c
*/

#include "menus.h"

list_t *get_all_levels_name(void)
{
    DIR *dir = opendir("./map/");
    list_t *levels = NULL;
    char *tmp;
    dirent_t *t;

    if (!dir)
        return NULL;
    while ((t = readdir(dir))) {
        tmp = str_concat(2, "./map/", t->d_name);
        if (is_file_valid(tmp))
            append_node(&levels, my_strdup(t->d_name));
        free(tmp);
    }
    return levels;
}

map_entry_t *create_entry(char const *file, sfVector2f size)
{
    map_entry_t *e = malloc(sizeof(map_entry_t));

    e->rtex = sfRenderTexture_create(size.x, size.y, false);
    e->icon = init_sprite(global_texture(), icon_rect,
    (sfVector2f){size.y, size.y});
    e->level_name = init_text(file, size.y * 0.9);
    scale_entry(e, size);
    return e;
}

void init_entries(map_select_t *m, sfVector2f size)
{
    list_t *tmp = get_all_levels_name();

    if (!tmp)
        return;
    while (tmp) {
        append_node(&(m->maps), create_entry(tmp->data,
        (sfVector2f){size.x, size.y * ENTRY_Y_SPAN}));
        remove_node(&tmp, 0, &free);
    }
}
