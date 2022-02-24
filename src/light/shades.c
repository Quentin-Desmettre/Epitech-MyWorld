/*
** EPITECH PROJECT, 2022
** Workshop3D v3.0
** File description:
** shades
*/

#include "world.h"

float get_time(world_t *world, win_t *win, float direction)
{
    
}

vertex_t *get_vertxs(world_t *world, triangle_t *tri)
{
    vertex_t *vertxs = malloc(sizeof(vertex_t) * 3);

    vertxs[0] = *tri->ptrs[0];
    vertxs[1] = *tri->ptrs[1];
    vertxs[2] = *tri->ptrs[2];
    return vertxs;
}

float calculate_shades(float vecs[2][3], float *light, vertex_t *vertxs)
{
    float direction;
    float normale[3];
    float light_dir[3] = {
    light[0] - (vertxs[0].pos[0] + vertxs[1].pos[0] + vertxs[2].pos[0]) / 3,
    light[1] - (vertxs[0].pos[1] + vertxs[1].pos[1] + vertxs[2].pos[1]) / 3,
    light[2] - (vertxs[0].pos[2] + vertxs[1].pos[2] + vertxs[2].pos[2]) / 3
    };

    normalize(vecs[0]);
    normalize(vecs[1]);
    crossproduct3(normale, vecs[0], vecs[1]);
    normalize(normale);
    normalize(light_dir);
    direction = dotproduct3(normale, light_dir);
    if (direction < 0)
        direction = 0;
    free(vertxs);
    return direction;
}

float apply_shades(world_t *world, triangle_t *tri)
{
    float *light;
    vertex_t *vertxs = get_vertxs(world, tri);
    float vecs[2][3] = {
    {vertxs[0].pos[0] - vertxs[1].pos[0],
    vertxs[0].pos[1] - vertxs[1].pos[1],
    vertxs[0].pos[2] - vertxs[1].pos[2]
    },
    {vertxs[0].pos[0] - vertxs[2].pos[0],
    vertxs[0].pos[1] - vertxs[2].pos[1],
    vertxs[0].pos[2] - vertxs[2].pos[2]
    }
    };

    return calculate_shades(vecs, world->light_source, vertxs);
}
