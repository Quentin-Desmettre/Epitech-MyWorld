/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** create.c
*/

#include "menus.h"

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
    g->win->map_size = size;
    free_lists(world);
    g->size = win_size;
    g->minimap = create_minimap((sfVector2f)
    {win_size.y * PART_OF_MINIMAP, win_size.y * PART_OF_MINIMAP}, size);
    g->dimension = size;
    g->gb = create_buttons((sfVector2f)
    {win_size.y * PART_OF_MINIMAP, win_size.y * (1 - PART_OF_MINIMAP)});
    return g;
}
