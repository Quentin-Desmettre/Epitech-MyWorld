/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** draw.c
*/

#include "menus.h"

void draw_world(game_t *g)
{
    sfSprite *s;

    if (sfKeyboard_isKeyPressed(sfKeyR))
        refresh_map(g->world, g->win);
    draw_back(g->world, g->win);
    draw_meshes(g->world, g->win);
    draw_fps(g->win);
    sfRenderTexture_display(g->win->r_tex);
    s = init_sprite_from_texture(sfRenderTexture_getTexture(g->win->r_tex));
    sfSprite_setPosition(s, (sfVector2f){g->size.y * PART_OF_MINIMAP, 0});
    sfRenderTexture_drawSprite(g->rtex, s, NULL);
    sfSprite_destroy(s);
    sfRenderTexture_clear(g->win->r_tex, sfBlack);
}

void draw_minimap_to_game(game_t *g)
{
    sfSprite *s;

    draw_minimap(g->minimap, g->world, g->dimension - 1);
    s = init_sprite_from_texture(sfRenderTexture_getTexture(g->minimap->rtex));
    sfSprite_scale(s, (sfVector2f){1, -1});
    sfSprite_setPosition(s, (sfVector2f){0, g->size.y * PART_OF_MINIMAP});
    sfRenderTexture_drawSprite(g->rtex, s, NULL);
    sfSprite_destroy(s);
    sfRenderTexture_clear(g->minimap->rtex, sfBlack);
}

void draw_gb_to_rtex(game_t *g)
{
    sfSprite *s = draw_gb(g);

    sfSprite_setPosition(s, (sfVector2f){0, g->size.y * PART_OF_MINIMAP});
    sfRenderTexture_drawSprite(g->rtex, s, NULL);
    sfSprite_destroy(s);
    if (g->gb->tool_tip_enabled)
        draw_tooltip(g, g->rtex);
}

const sfTexture *draw_game(void *game)
{
    game_t *g = game;

    sfRenderTexture_clear(g->rtex, sfBlack);
    draw_world(g);
    draw_minimap_to_game(g);
    draw_gb_to_rtex(g);
    sfRenderTexture_display(g->rtex);
    return sfRenderTexture_getTexture(g->rtex);
}
