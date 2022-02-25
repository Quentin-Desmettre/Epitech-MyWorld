/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** create.c
*/

#include "menus.h"

#define DEFAULT_2F (sfVector2f){1, 1}

static const float mc_pos_fac[4][2] = {
    {0.11, 0.65}, {0.755, 0.65}, {0.55, 0.85}, {0.78, 0.85}
};

static const float mc_size_fac[4][2] = {
    {0.06, 0.06}, {0.06, 0.1}, {0.18, 0.1}, {0.18, 0.1}
};

void scale_map_create(map_create_t *mc, sfVector2f win_size)
{
    sfVector2f new_size;

    sfRenderTexture_destroy(mc->rtex);
    mc->rtex = sfRenderTexture_create(win_size.x, win_size.y, 0);
    sfText_setCharacterSize(mc->name_prompt, win_size.y * MAIN_MENU_TXT_FACTOR * 0.13);
    sfText_setCharacterSize(mc->size, win_size.y * MAIN_MENU_TXT_FACTOR * 0.13);
    scale_line_edit(mc->name,
    (sfVector2f){win_size.x * 0.9, win_size.y * 0.2});
    rescale_slider(mc->size_slider,
    (sfVector2f){win_size.x * 0.5, win_size.y * 0.1},
    (sfVector2f){win_size.x * 0.205, win_size.y * 0.64});
    for (int i = 0; i < 4; i++) {
        new_size = (sfVector2f)
        {win_size.x * mc_size_fac[i][0], win_size.y * mc_size_fac[i][1]};
        if (i < 2)
            new_size.y = new_size.x;
        set_sprite_size(mc->buttons[i]->sprite, new_size);
        mc->buttons[i]->size = new_size;
    }
}

void move_mc(map_create_t *mc, sfVector2f ws)
{
    sfVector2f new_pos;

    sfText_setPosition(mc->name_prompt, (sfVector2f){ws.x * 0.28, ws.y * 0.07});
    sfText_setPosition(mc->size, (sfVector2f){ws.x * 0.33, ws.y * 0.5});
    for (int i = 0; i < 4; i++) {
        new_pos = (sfVector2f)
        {ws.x * mc_pos_fac[i][0], ws.y * mc_pos_fac[i][1]};
        sfSprite_setPosition(mc->buttons[i]->sprite, new_pos);
        mc->buttons[i]->pos = new_pos;
    }
}

void scale_mc(map_create_t *mc, sfVector2f win_size)
{
    move_mc(mc, win_size);
    scale_map_create(mc, win_size);
}

const sfTexture *draw_mc(map_create_t *mc, sfVector2f ws)
{
    sfSprite *s;

    sfRenderTexture_clear(mc->rtex, sfBlack);
    sfRenderTexture_drawText(mc->rtex, mc->name_prompt, NULL);
    s = draw_line_edit(mc->name, (sfVector2f){ws.x * 0.04, ws.y * 0.23});
    sfRenderTexture_drawSprite(mc->rtex, s, NULL);
    sfSprite_destroy(s);
    sfRenderTexture_drawText(mc->rtex, mc->size, NULL);
    s = draw_slider(mc->size_slider);
    sfRenderTexture_drawSprite(mc->rtex, s, NULL);
    sfSprite_destroy(s);
    for (int i = 0; i < 4; i++)
        draw_button_to_rtex(mc->buttons[i], mc->rtex);
    sfRenderTexture_display(mc->rtex);
    return (sfRenderTexture_getTexture(mc->rtex));
}

map_create_t *create_map_create(sfVector2f win_size)
{
    map_create_t *mc = malloc(sizeof(map_create_t));

    void (*ptrs[4])(void *) = {
        increase_size, decrease_size, launch_size, mc_go_back
    };

    mc->rtex = sfRenderTexture_create(win_size.x, win_size.y, 0);
    mc->name_prompt =
    init_text("Map name: ", win_size.y * MAIN_MENU_TXT_FACTOR);
    mc->name = create_line_edit(
    (sfVector2f){win_size.x * 0.8, win_size.y * 0.2}, "my map 0");
    mc->size = init_text("64x64", win_size.y * MAIN_MENU_TXT_FACTOR);
    mc->size_slider = create_slider(
    (sfVector2f){win_size.x * 0.8, win_size.y * 0.2},
    (sfVector2f){16, 256}, 64, (sfVector2f){1, 1});
    for (int i = 0; i < 4; i++)
        mc->buttons[i] = init_button(global_texture(),
        mc_rects[i], DEFAULT_2F, DEFAULT_2F, "", ptrs[i]);
    scale_mc(mc, win_size);
    return mc;
}
