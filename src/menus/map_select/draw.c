/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** draw.c
*/

#include "menus.h"

sfSprite *draw_entry(map_entry_t *m)
{
    sfRenderTexture_clear(m->rtex, sfTransparent);

    sfRenderTexture_drawSprite(m->rtex, m->icon, NULL);
    sfRenderTexture_drawText(m->rtex, m->level_name, NULL);

    sfRenderTexture_display(m->rtex);
    return init_sprite_from_texture(sfRenderTexture_getTexture(m->rtex));
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
