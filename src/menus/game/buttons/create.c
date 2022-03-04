/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** create.c
*/

#include "menus.h"

void draw_box(button_t *but, sfRenderTexture *rtex)
{
    sfRectangleShape *shape = sfRectangleShape_create();

    sfRectangleShape_setSize(shape, but->size);
    sfRectangleShape_setFillColor(shape, sfTransparent);
    sfRectangleShape_setOutlineColor(shape, sfWhite);
    sfRectangleShape_setPosition(shape, but->pos);
    sfRectangleShape_setOutlineThickness(shape, but->size.x * 0.05);
    sfRectangleShape_setOrigin(shape,
    (sfVector2f){but->size.x * 0.5, but->size.y * 0.5});
    sfRenderTexture_drawRectangleShape(rtex, shape, NULL);
    sfRectangleShape_destroy(shape);
}

sfSprite *draw_gb(game_t *ga)
{
    game_buttons_t *g = ga->gb;

    sfRenderTexture_clear(g->rtex, sfBlack);

    for (int i = 0; i < 10; i++) {
        draw_button_to_rtex(g->buttons[i], g->rtex);
        if (i == g->selected)
            draw_box(g->buttons[i], g->rtex);
    }
    sfRenderTexture_display(g->rtex);
    return init_sprite_from_texture(sfRenderTexture_getTexture(g->rtex));
}

void create_tooltip(game_buttons_t *g, sfVector2f tex_size)
{
    g->tooltip = init_text("", tex_size.y * 0.075);
    sfText_setColor(g->tooltip, sfBlack);
    g->tooltip_box = create_rectangle((sfVector2f){1, 1}, sfYellow, NULL);
    g->tool_tip_enabled = false;
}

game_buttons_t *create_buttons(sfVector2f size)
{
    game_buttons_t *g = malloc(sizeof(game_buttons_t));
    sfVector2f pos;
    sfVector2f n_size;
    float size_factor;

    g->rtex = sfRenderTexture_create(size.x, size.y, 0);
    for (int i = 0; i < 10; i++) {
        pos = (sfVector2f){size.x * (gb_pos[i][0]), size.y * (gb_pos[i][1])};
        n_size = (sfVector2f){size.x * gb_size[i][0], size.y * gb_size[i][1]};
        g->buttons[i] = init_button(global_texture(),
        game_button_rects[i % 1], pos, n_size, "", NULL);
        center_sprite(g->buttons[i]->sprite);
    }
    g->border = create_rectangle((sfVector2f){1, 1}, sfWhite, NULL);
    g->selected = 0;
    g->tip_clock = sfClock_create();
    create_tooltip(g, size);
    g->mouse_pos = (sfVector2f){0, 0};
    return g;
}
