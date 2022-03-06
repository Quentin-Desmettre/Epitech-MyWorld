/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** create.c
*/

#include "menus.h"

void destroy_game_struct(game_t *game)
{
    destroy_gbuttons(game->gb);
    destroy_minimap(game->minimap);
    sfRenderTexture_destroy(game->rtex);
    game->world->destroy(game->world);
    game->win->destroy(game->win);
    free(game);
}

void create_other(game_t *g, unsigned size, sfVector2f win_size)
{
    g->size = win_size;
    g->minimap = create_minimap((sfVector2f)
    {win_size.y * PART_OF_MINIMAP, win_size.y * PART_OF_MINIMAP}, size);
    g->dimension = size;
    g->gb = create_buttons((sfVector2f)
    {win_size.y * PART_OF_MINIMAP, win_size.y * (1 - PART_OF_MINIMAP)});
}

void start_world(game_t *g)
{
    world_t *world;
    sfVector2f win_size = g->size;

    g->world = create_world();
    srand((unsigned)(unsigned long)(g->world));
    world = g->world;
    create_map(world, g->dimension);
    set_light_source(world, g->dimension / 2.0, 1, 1000);
    convert_to_array(world);
    world->sortBuffer = malloc(sizeof(vecsort_t) * world->nb_trig);
    world->sortBuffer2 = malloc(sizeof(vecsort_t) * world->nb_trig);
    g->win = win_create(world->nb_trig,
    (sfVector2f){win_size.x - win_size.y * PART_OF_MINIMAP, win_size.y});
    g->win->map_size = g->dimension;
    get_gradient(1);
    smooth_shadow(world, g->win);
    free_lists(world);
    center_cam(&(g->world->matrix));
}

game_t *create_game(unsigned size, sfVector2f win_size)
{
    game_t *g = malloc(sizeof(game_t));

    create_other(g, size, win_size);
    size++;
    g->rtex = sfRenderTexture_create(win_size.x, win_size.y, 0);
    start_world(g);
    return g;
}
