/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** create.c
*/

#include "menus.h"

void destroy_game_struct(game_t *game)
{
    sfRenderTexture_destroy(game->rtex);
    game->world->destroy(game->world);
    game->win->destroy(game->win);
    sfRenderTexture_destroy(game->minimap->rtex);
    sfVertexArray_destroy(game->minimap->array);
    free(game->minimap->tmp);
    sfCircleShape_destroy(game->minimap->circle);
    sfClock_destroy(game->minimap->time);
    for (int i = 0; i < 10; i++)
        destroy_button(game->gb->buttons[i]);
    sfRenderTexture_destroy(game->gb->rtex);
    sfClock_destroy(game->gb->tip_clock);
    sfRectangleShape_destroy(game->gb->border);
    sfRectangleShape_destroy(game->gb->tooltip_box);
    sfText_destroy(game->gb->tooltip);
    free(game);
}

void create_other(game_t *g, unsigned size, sfVector2f win_size)
{
    g->win->map_size = size;
    g->size = win_size;
    g->minimap = create_minimap((sfVector2f)
    {win_size.y * PART_OF_MINIMAP, win_size.y * PART_OF_MINIMAP}, size);
    g->dimension = size;
    g->gb = create_buttons((sfVector2f)
    {win_size.y * PART_OF_MINIMAP, win_size.y * (1 - PART_OF_MINIMAP)});
}

game_t *create_game(unsigned size, sfVector2f win_size)
{
    game_t *g = malloc(sizeof(game_t));
    world_t *world;

    size++;
    g->rtex = sfRenderTexture_create(win_size.x, win_size.y, 0);
    g->world = create_world();
    world = g->world;
    create_map(world, size);
    set_light_source(world, size / 2.0, 1, 1000);
    convert_to_array(world);
    world->sortBuffer = malloc(sizeof(vecsort_t) * world->nb_trig);
    world->sortBuffer2 = malloc(sizeof(vecsort_t) * world->nb_trig);
    g->win = win_create(world->nb_trig,
    (sfVector2f){win_size.x - win_size.y * PART_OF_MINIMAP, win_size.y});
    free_lists(world);
    create_other(g, size, win_size);
    return g;
}
