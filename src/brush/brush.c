/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "world.h"

void update_color(world_t *world)
{
    float height;

    for (size_t i = 0; i < world->nb_trig; i++) {
        height = get_max_height(world->a_triangles[i]);
        if (height > 12)
            world->a_triangles[i].color = sfWhite;
        else if (height < -10)
            world->a_triangles[i].color = sfBlue;
        else
            world->a_triangles[i].color = sfGreen;
    }
}

void up_br(world_t *world, minimap_t *map)
{
    float nb = map->size.y / (float)(map->map_size);
    int size = map->map_size;
    int x = (int)(round(map->mouse_pos.x / nb));
    int y = (int)(round(map->mouse_pos.y / nb));
    if (x < 0 || y < 0 || x > size || y > size)
        return;
    for (int i = x - map->s_br; i < x + map->s_br; i++) {
        if (i < 0 || i >= size)
            continue;
        for (int j = y - map->s_br; j < y + map->s_br; j++) {
            ((size - j) >= 0 && (size - j) < (size) && world->a_vertxs
            [i * (size) + (size - j)]->pos[1] < 40) ?
            world->a_vertxs[i * (size) + (size - j)]->
            pos[1] += 1 : 0;
        }
    }
}

void down_br(world_t *world, minimap_t *map)
{
    float nb = map->size.y / (float)(map->map_size);
    int size = (int)map->map_size;
    int x = (int)(round(map->mouse_pos.x / nb));
    int y = (int)(round(map->mouse_pos.y / nb));
    if (x < 0 || y < 0 || x > size || y > size)
        return;
    for (int i = x - map->s_br; i < x + map->s_br; i++) {
        if (i < 0 || i >= size)
            continue;
        for (int j = y - map->s_br; j < y + map->s_br; j++) {
            ((size - j) >= 0 && (size - j) < (size) && world->a_vertxs
            [i * (size) + (size - j)]->pos[1] > -10) ?
            world->a_vertxs[i * (size) + (size - j)]->
            pos[1] -= 1 : 0;
        }
    }
}

void average_br(world_t *world, minimap_t *map)
{
    float nb = map->size.y / (float)(map->map_size);
    int size = map->map_size;
    int x = (int)(round(map->mouse_pos.x / nb));
    int y = (int)(round(map->mouse_pos.y / nb));
    int tmp = 0;
    int count = 0;
    if (x < 0 || y < 0 || x > size || y > size)
        return;
    for (int i = x - map->s_br; i < x + map->s_br; i++) {
        if (i < 0 || i >= size)
            continue;
        for (int j = y - map->s_br; j < y + map->s_br; j++) {
            ((size - j) >= 0 && (size - j) < (size) && world->a_vertxs
            [i * (size) + (size - j)]->pos[1] > -10) ?
            tmp += world->a_vertxs[i * (size) + (size - j)]->
            pos[1], count++: 0;
        }
    }
    if (count == 0)
        return;
    tmp /= count;
    for (int i = x - map->s_br; i < x + map->s_br; i++) {
        if (i < 0 || i >= size)
            continue;
        for (int j = y - map->s_br; j < y + map->s_br; j++) {
            ((size - j) >= 0 && (size - j) < (size) && world->a_vertxs
            [i * (size) + (size - j)]->pos[1] > -10) ?
            (world->a_vertxs[i * (size) + (size - j)]->
            pos[1] = (world->a_vertxs[i * (size) + (size - j)]->
            pos[1] + tmp) / 2): 0;
        }
    }
}

void average_w_br(world_t *world, minimap_t *map)
{
    float nb = map->size.y / (float)(map->map_size);
    int size = map->map_size;
    int x = (int)(round(map->mouse_pos.x / nb));
    int y = (int)(round(map->mouse_pos.y / nb));
    int tmp = 0;
    int count = 0;
    if (x < 0 || y < 0 || x > size || y > size)
        return;
    for (int i = x - map->s_br; i < x + map->s_br; i++) {
        if (i < 0 || i >= size)
            continue;
        for (int j = y - map->s_br; j < y + map->s_br; j++) {
            ((size - j) >= 0 && (size - j) < (size)) ?
            tmp += world->a_vertxs[i * (size) + (size - j)]->
            pos[1], count++ : 0;
        }
    }
    if (count == 0)
        return;
    tmp /= count;
    for (int i = x - map->s_br; i < x + map->s_br; i++) {
        if (i < 0 || i >= size)
            continue;
        for (int j = y - map->s_br; j < y + map->s_br; j++) {
            ((size - j) >= 0 && (size - j) < (size)) ?
            (world->a_vertxs[i * (size) + (size - j)]->
            pos[1] = (world->a_vertxs[i * (size) + (size - j)]->
            pos[1] + tmp) / 2): 0;
        }
    }
}

void average_d_br(world_t *world, minimap_t *map)
{
    float nb = map->size.y / (float)(map->map_size);
    int size = map->map_size;
    int x = (int)(round(map->mouse_pos.x / nb));
    int y = (int)(round(map->mouse_pos.y / nb));
    int tmp = 41;
    int count = 0;

    if (x < 0 || y < 0 || x > size || y > size)
        return;
    for (int i = x - map->s_br; i < x + map->s_br; i++) {
        if (i < 0 || i >= size)
            continue;
        for (int j = y - map->s_br; j < y + map->s_br; j++) {
            ((size - j) >= 0 && (size - j) < (size) && world->a_vertxs
            [i * (size) + (size - j)]->pos[1] > -10 && world->a_vertxs
            [i * (size) + (size - j)]->pos[1] < tmp) ?
            tmp = world->a_vertxs[i * (size) + (size - j)]->
            pos[1]: 0;
        }
    }
    for (int i = x - map->s_br; i < x + map->s_br; i++) {
        if (i < 0 || i >= size)
            continue;
        for (int j = y - map->s_br; j < y + map->s_br; j++) {
            ((size - j) >= 0 && (size - j) < (size) && world->a_vertxs
            [i * (size) + (size - j)]->pos[1] > -10) ?
            (world->a_vertxs[i * (size) + (size - j)]->
            pos[1] = (world->a_vertxs[i * (size) + (size - j)]->
            pos[1] + tmp) / 2): 0;
        }
    }
}
