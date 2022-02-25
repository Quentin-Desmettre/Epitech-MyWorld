/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** release.c
*/

#include "menus.h"

void destroy_mc(map_create_t *mc)
{
    destroy_line_edit(mc->name);
    sfText_destroy(mc->name_prompt);
    sfText_destroy(mc->size);
    destroy_slider(mc->size_slider);
    sfRenderTexture_destroy(mc->rtex);
    for (int i = 0; i < 4; i++)
        destroy_button(mc->buttons[i]);
    free(mc);
}

void release_mc(map_create_t *mc, int index, window_t *win)
{
    for (int i = 0; i < 4; i++)
        press_button(mc->buttons[i], false);
    if (index >= 0 && index < 4)
        mc->buttons[index]->action(win);
}
