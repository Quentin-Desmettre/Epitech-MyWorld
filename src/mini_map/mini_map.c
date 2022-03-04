/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "world.h"

void destroy_minimap(minimap_t *m)
{
    free(m->tmp);
    sfClock_destroy(m->time);
    sfRenderTexture_destroy(m->rtex);
    sfCircleShape_destroy(m->circle);
    sfVertexArray_destroy(m->array);
    free(m);
}

void init_functions(minimap_t *m)
{
    void (*actions[NB_ACTIONS])(world_t *, minimap_t *) = {
        &average_d_br, &average_br, &average_w_br, &up_br, &down_br
    };

    for (int i = 0; i < NB_ACTIONS; i++)
        m->actions[i] = actions[i];
}

minimap_t *create_minimap(sfVector2f size, int map_size)
{
    minimap_t *m = malloc(sizeof(minimap_t));

    m->rtex = sfRenderTexture_create(size.x, size.y, 0);
    m->array = sfVertexArray_create();
    sfVertexArray_resize(m->array, map_size);
    m->tmp = malloc(sizeof(sfVertex));
    for (size_t i = 0; i < sizeof(sfVertex); i++)
        ((char *)(m->tmp))[i] = 0;
    m->size = size;
    m->s_br = 1;
    m->mouse_pos = (sfVector2f){10, 10};
    m->state = 4;
    m->map_size = map_size;
    m->circle = sfCircleShape_create();
    m->time = sfClock_create();
    sfCircleShape_setOutlineColor(m->circle, sfWhite);
    sfCircleShape_setOutlineThickness(m->circle, 1.0);
    sfCircleShape_setFillColor(m->circle, sfTransparent);
    init_functions(m);
    return m;
}
