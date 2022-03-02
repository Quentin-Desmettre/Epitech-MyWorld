/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** refresh
*/

#include "world.h"

void refresh_map(world_t *world, win_t *win)
{
    free(world->a_vertxs);
    free(world->a_triangles);
    free(world->projected);
    world->nb_meshes = 0;
    world->nb_vertxs = 0;
    world->nb_trig = 0;
    world->meshes = malloc(sizeof(list_t *));
    *world->meshes = NULL;
    world->vertxs = malloc(sizeof(list_t *));
    *world->vertxs = NULL;
    world->triangles = malloc(sizeof(list_t *));
    *world->triangles = NULL;
    srand((unsigned)(unsigned long)(&world->a_vertxs[0]));
    get_gradient(1);
    create_map(world, win->map_size);
    set_light_source(world, world->light_source[0],
    world->light_source[1], world->light_source[2]);
    convert_to_array(world);
    free_lists(world);
    smooth_shadow(world, win);
}
