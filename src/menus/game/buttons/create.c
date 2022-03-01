/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** create.c
*/

#include "menus.h"

static const char *tips[10] = {
    "Rise up the selected area",
    "Smooth all the selected points towards the average height",
    "Add water on the selected area",
    "Lower the selected area",
    "Smooth all the selected points toward the lowest point",
    "Save the map",
    "Pause the time",
    "Shift the in-game time by +1 hour",
    "Shift the in-game time by -1 hour",
    "Help"
};

static const sfIntRect game_button_rects[] = {
    {0, 0, 1, 1}
};

static const float gb_pos[10][2] = {
    {0.0625, 0.25 / 4}, {0.37, 0.25 / 4}, {0.67, 0.25 / 4},
    {0.0625, 0.37}, {0.37, 0.37}, {0.67, 0.37},
    {0.0625, 0.67}, {0.3, 0.67}, {0.53, 0.67}, {0.77, 0.67},
};

static const float gb_size[10][2] = {
    {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25},
    {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25},
    {0.15, 0.25}, {0.15, 0.25}, {0.15, 0.25}, {0.15, 0.25}
};

void draw_box(button_t *but, sfRenderTexture *rtex)
{
    sfRectangleShape *shape = sfRectangleShape_create();

    sfRectangleShape_setSize(shape, but->size);
    sfRectangleShape_setFillColor(shape, sfTransparent);
    sfRectangleShape_setOutlineColor(shape, sfWhite);
    sfRectangleShape_setPosition(shape, but->pos);
    sfRectangleShape_setOutlineThickness(shape, but->size.x * 0.05);
    sfRenderTexture_drawRectangleShape(rtex, shape, NULL);
    sfRectangleShape_destroy(shape);
}

void gb_events(game_buttons_t *g, sfEvent ev, sfVector2f pos)
{
    if (ev.type == sfEvtMouseButtonPressed) {
        ev.mouseButton.x -= pos.x;
        ev.mouseButton.y -= pos.y;
        check_button_press(g->buttons, 10, ev);
    }
    if (ev.type == sfEvtMouseMoved) {
        ev.mouseMove.x -= pos.x;
        ev.mouseMove.y -= pos.y;
        check_button_move(g->buttons, 10, ev);
    }
    if (ev.type == sfEvtMouseButtonReleased) {
        ev.mouseButton.x -= pos.x;
        ev.mouseButton.y -= pos.y;
        int tmp = button_at(g->buttons, 10, ev);
        if (tmp >= 0 && tmp < 6)
            g->selected = tmp;
    }
}

sfSprite *draw_gb(game_buttons_t *g)
{
    sfRenderTexture_clear(g->rtex, sfBlack);

    for (int i = 0; i < 10; i++) {
        draw_button_to_rtex(g->buttons[i], g->rtex);
        if (i == g->selected)
            draw_box(g->buttons[i], g->rtex);
    }
    sfRenderTexture_display(g->rtex);
    return init_sprite_from_texture(sfRenderTexture_getTexture(g->rtex));
}

game_buttons_t *create_buttons(sfVector2f size)
{
    game_buttons_t *g = malloc(sizeof(game_buttons_t));
    sfVector2f pos;
    sfVector2f n_size;
    float size_factor;

    g->rtex = sfRenderTexture_create(size.x, size.y, 0);
    for (int i = 0; i < 10; i++) {
        pos = (sfVector2f){size.x * gb_pos[i][0], size.y * gb_pos[i][1]};
        n_size = (sfVector2f){size.x * gb_size[i][0], size.y * gb_size[i][1]};
        g->buttons[i] = init_button(global_texture(),
        game_button_rects[i % 1], pos, n_size, "", NULL);
    }
    g->border = create_rectangle((sfVector2f){1, 1}, sfWhite, NULL);
    g->selected = 0;
    g->tip_clock = sfClock_create();
    return g;
}
