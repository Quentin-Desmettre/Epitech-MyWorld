/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** create.c
*/


#include "menus.h"
#include "list.h"
#include <sys/types.h>
#include <dirent.h>

#define SEMI_COLOR ((sfColor){127, 127, 127, 255})
#define SEMI_TRANSP ((sfColor){127, 127, 127, 127})

#define ENTRY_Y_SPAN 0.12

typedef struct dirent dirent_t;

static const sfIntRect icon_rect = {0, 0, 1, 1};

static const sfIntRect background_rect = {0, 0, 1, 1};

static const sfIntRect but_rects[3] = {
    {0, 0, 1, 1}, {0, 0, 1, 1}, {0, 0, 1, 1}
};

static const sfIntRect hider_rect = {1, 0, 1, 1};

static const float select_pf[3][2] = {
    {0.18, 0.9}, {0.5, 0.9}, {0.82, 0.9}
};

static const float select_sf[2] = {0.27, 0.1};

void scale_entry(map_entry_t *entry, sfVector2f size)
{
    sfFloatRect sp_bnds;

    sfRenderTexture_destroy(entry->rtex);
    entry->rtex = sfRenderTexture_create(size.x, size.y, false);
    set_sprite_size(entry->icon, (sfVector2f){size.y, size.y});

    sp_bnds = sfSprite_getGlobalBounds(entry->icon);
    sfText_setCharacterSize(entry->level_name, size.y * 0.6);
    sfText_setPosition(entry->level_name,
    (sfVector2f){sp_bnds.width * 1.1, size.y * 0.2});
}

map_entry_t *create_entry(char const *file, sfVector2f size)
{
    map_entry_t *e = malloc(sizeof(map_entry_t));

    e->rtex = sfRenderTexture_create(size.x, size.y, false);
    e->icon = init_sprite(global_texture(), icon_rect, (sfVector2f){size.y, size.y});
    e->level_name = init_text(file, size.y * 0.9);
    scale_entry(e, size);
    return e;
}

sfSprite *draw_entry(map_entry_t *m)
{
    sfRenderTexture_clear(m->rtex, sfTransparent);

    sfRenderTexture_drawSprite(m->rtex, m->icon, NULL);
    sfRenderTexture_drawText(m->rtex, m->level_name, NULL);

    sfRenderTexture_display(m->rtex);
    return init_sprite_from_texture(sfRenderTexture_getTexture(m->rtex));
}

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

void scale_select(map_select_t *m, sfVector2f size)
{
    list_t *tmp = m->maps;
    sfVector2f pos;

    m->size = size;
    sfRenderTexture_destroy(m->rtex);
    m->rtex = sfRenderTexture_create(size.x, size.y, 0);
    for (int i = 0; i < 3; i++) {
        pos = (sfVector2f){size.x * select_pf[i][0], size.y * select_pf[i][1]};
        m->buttons[i]->pos = pos;
        sfSprite_setPosition(m->buttons[i]->sprite, pos);
        m->buttons[i]->size =
        (sfVector2f){size.x * select_sf[0], size.y * select_sf[1]};
        set_sprite_size(m->buttons[i]->sprite, m->buttons[i]->size);
    }
    set_sprite_size(m->hider, (sfVector2f){size.x, size.y * 0.2});
    sfSprite_setPosition(m->hider, (sfVector2f){0, size.y * 0.8});
    if (!tmp)
        return;
    do {
        scale_entry(tmp->data, (sfVector2f){size.x, size.y * ENTRY_Y_SPAN});
        tmp = tmp->next;
    } while (tmp != m->maps);
}

void draw_box_around(sfSprite *s, map_select_t *ms, sfColor color)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(s);

    sfRectangleShape_setSize(ms->box, (sfVector2f){rect.width, rect.height});
    sfRectangleShape_setOutlineColor(ms->box, color);
    sfRectangleShape_setFillColor(ms->box, sfTransparent);
    sfRectangleShape_setPosition(ms->box, (sfVector2f){rect.left, rect.top});
    sfRectangleShape_setOutlineThickness(ms->box, 6);
    sfRenderTexture_drawRectangleShape(ms->rtex, ms->box, NULL);
}

void draw_entries(map_select_t *m)
{
    sfSprite *s;
    list_t *tmp = m->maps;
    sfVector2f pos = {m->size.x * 0.05, m->size.x * 0.05 - m->x_start};
    int i = 0;

    do {
        s = draw_entry(tmp->data);
        sfSprite_setPosition(s, pos);
        if (i == m->primary)
            draw_box_around(s, m, sfWhite);
        if (i != m->primary && i == m->secondary)
            draw_box_around(s, m, SEMI_TRANSP);
        sfRenderTexture_drawSprite(m->rtex, s, NULL);
        sfSprite_destroy(s);
        pos.y += m->size.y * ENTRY_Y_SPAN * ENTRY_SPACING;
        tmp = tmp->next;
        i++;
    } while (m->maps != tmp);
}

const sfTexture *draw_select(void *mm)
{
    map_select_t *m = mm;

    sfRenderTexture_clear(m->rtex, sfBlack);

    //sfRenderTexture_drawSprite(m->rtex, m->background, NULL);
    if (m->maps)
        draw_entries(m);
    sfRenderTexture_drawSprite(m->rtex, m->hider, NULL);
    for (int i = 1; i < 3; i++)
        sfSprite_setColor(m->buttons[i]->sprite,
        m->primary < 0 ? SEMI_COLOR : sfWhite);
    for (int i = 0; i < 3; i++)
        draw_button_to_rtex(m->buttons[i], m->rtex);
    sfRenderTexture_display(m->rtex);
    return sfRenderTexture_getTexture(m->rtex);
}

map_select_t *create_map_select(sfVector2f size)
{
    map_select_t *m = malloc(sizeof(map_select_t));

    m->rtex = sfRenderTexture_create(size.x, size.y, false);
    m->maps = NULL;
    for (int i = 0; i < 3; i++) {
        m->buttons[i] = init_button(global_texture(), but_rects[i],
        (sfVector2f){0, 0},
        (sfVector2f){size.x * select_sf[0], size.y * select_sf[1]}, "", NULL);
        center_sprite(m->buttons[i]->sprite);
    }
    m->size = size;
    m->background = init_sprite(global_texture(), background_rect, size);
    m->box = sfRectangleShape_create();
    m->hider = init_sprite(global_texture(),
    hider_rect, (sfVector2f){size.x, size.y * 0.3});
    init_entries(m, size);
    scale_select(m, size);
    m->primary = -1;
    m->secondary = -1;
    m->x_start = 0;
    return m;
}
