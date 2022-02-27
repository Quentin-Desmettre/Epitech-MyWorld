/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "world.h"

void app_point(float x, float y, minimap_t *map)
{
    map->tmp->position = (sfVector2f){x, y};
    sfVertexArray_append(map->array, *map->tmp);
}

void where_minimap(world_t *world, minimap_t *map, long long size)
{
    float nb = height / (float)(size);
    int x = (int)(round(map->mouse_pos.x / nb));
    int y = (int)(round(map->mouse_pos.y / nb));
    float xx;
    float yy;
    if (x < 0 || y < 0 || x > size || y > size)
        return;
    xx = world->a_vertxs[x * (size + 1) + y]->pos[0] / 1.5;
    yy = world->a_vertxs[x * (size + 1) + y]->pos[2] / 1.5;
    map->tmp->color = sfWhite;
    app_point((xx - map->s_br) * nb, (yy + map->s_br) * nb, map);
    app_point((xx - map->s_br) * nb, (yy - map->s_br) * nb, map);
    app_point((xx + map->s_br) * nb, (yy - map->s_br) * nb, map);
    app_point((xx + map->s_br) * nb, (yy + map->s_br) * nb, map);
    app_point((xx - map->s_br) * nb, (yy + map->s_br) * nb, map);
    sfVertexArray_setPrimitiveType(map->array, sfLinesStrip);
    sfRenderTexture_drawVertexArray(map->rtex, map->array, 0);
    sfVertexArray_clear(map->array);
}

void add_color(int i, minimap_t *map, world_t *world, const float *time)
{
    float direction = world->a_triangles[i]->direction;

    map->tmp->color = world->a_triangles[i]->color;
    map->tmp->color.r *= direction;
    map->tmp->color.g *= direction;
    map->tmp->color.b *= direction;
}

void draw_minimap(minimap_t *map, world_t *world, sfBool day, int size)
{
    const float *time = day ? day_light : night_light;
    float nb = map->size.y / (float)(size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            add_color(i * size + j, map, world, time);
            app_point(nb * i, nb * (size - j - 1), map);
            app_point(nb * (i + 1), nb * (size - j - 1), map);
            app_point(nb * i, nb * (size - j), map);
            add_color(i * size + j + size * size, map, world, time);
            app_point(nb * (i + 1), nb * (size - j), map);
            app_point(nb * (i + 1), nb * (size - j - 1), map);
            app_point(nb * i, nb * (size - j), map);
        }
    }
    sfVertexArray_setPrimitiveType(map->array, sfTriangles);
    sfRenderTexture_drawVertexArray(map->rtex, map->array, 0);
    sfVertexArray_clear(map->array);
    where_minimap(world, map, size);
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
    m->state = 0;
    return m;
}
