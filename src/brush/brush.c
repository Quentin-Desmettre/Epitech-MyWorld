/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "world.h"

// void up_br(world_t *world, win_t *win, sfVector2i pos)
// {
//     float nb = height / (float)(win->map_size);
//     int size = (int)win->map_size;
//     int x = (int)(round(sfMouse_getPositionRenderWindow(win->window).x / nb));
//     int y = (int)(round(sfMouse_getPositionRenderWindow(win->window).y / nb));
//     if (x < 0 || y < 0 || x > size || y > size)
//         return;
//     for (int i = x - world->s_br; i < x + world->s_br; i++) {
//         if (i < 0 || i >= size)
//             continue;
//         for (int j = y - world->s_br; j < y + world->s_br; j++) {
//             ((size - j) >= 0 && (size - j) < (size) && world->a_vertxs
//             [i * (size) + (size - j)]->pos[1] < 40) ?
//             world->a_vertxs[i * (size) + (size - j)]->
//             pos[1] += 1 : 0;
//         }
//     }
// }

// void down_br(world_t *world, win_t *win, sfVector2i pos)
// {
//     float nb = height / (float)(win->map_size);
//     int size = (int)win->map_size;
//     int x = (int)(round(sfMouse_getPositionRenderWindow(win->window).x / nb));
//     int y = (int)(round(sfMouse_getPositionRenderWindow(win->window).y / nb));
//     if (x < 0 || y < 0 || x > size || y > size)
//         return;
//     for (int i = x - world->s_br; i < x + world->s_br; i++) {
//         if (i < 0 || i >= size)
//             continue;
//         for (int j = y - world->s_br; j < y + world->s_br; j++) {
//             ((size - j) >= 0 && (size - j) < (size) && world->a_vertxs
//             [i * (size) + (size - j)]->pos[1] > -10) ?
//             world->a_vertxs[i * (size) + (size - j)]->
//             pos[1] -= 1 : 0;
//         }
//     }
// }

// void average_br(world_t *world, win_t *win, sfVector2i pos)
// {
//     float nb = height / (float)(win->map_size);
//     int size = (int)win->map_size;
//     int x = (int)(round(sfMouse_getPositionRenderWindow(win->window).x / nb));
//     int y = (int)(round(sfMouse_getPositionRenderWindow(win->window).y / nb));
//     int tmp = 0;
//     int count = 0;
//     if (x < 0 || y < 0 || x > size || y > size)
//         return;
//     for (int i = x - world->s_br; i < x + world->s_br; i++) {
//         if (i < 0 || i >= size)
//             continue;
//         for (int j = y - world->s_br; j < y + world->s_br; j++) {
//             ((size - j) >= 0 && (size - j) < (size) && world->a_vertxs
//             [i * (size) + (size - j)]->pos[1] > -10) ?
//             tmp += world->a_vertxs[i * (size) + (size - j)]->
//             pos[1], count++: 0;
//         }
//     }
//     if (count == 0)
//         return;
//     tmp /= count;
//     for (int i = x - world->s_br; i < x + world->s_br; i++) {
//         if (i < 0 || i >= size)
//             continue;
//         for (int j = y - world->s_br; j < y + world->s_br; j++) {
//             ((size - j) >= 0 && (size - j) < (size) && world->a_vertxs
//             [i * (size) + (size - j)]->pos[1] > -10) ?
//             (world->a_vertxs[i * (size) + (size - j)]->
//             pos[1] = (world->a_vertxs[i * (size) + (size - j)]->
//             pos[1] + tmp) / 2): 0;
//         }
//     }
// }

// void average_w_br(world_t *world, win_t *win, sfVector2i pos)
// {
//     float nb = height / (float)(win->map_size);
//     int size = (int)win->map_size;
//     int x = (int)(round(sfMouse_getPositionRenderWindow(win->window).x / nb));
//     int y = (int)(round(sfMouse_getPositionRenderWindow(win->window).y / nb));
//     int tmp = 0;
//     int count = 0;
//     if (x < 0 || y < 0 || x > size || y > size)
//         return;
//     for (int i = x - world->s_br; i < x + world->s_br; i++) {
//         if (i < 0 || i >= size)
//             continue;
//         for (int j = y - world->s_br; j < y + world->s_br; j++) {
//             ((size - j) >= 0 && (size - j) < (size)) ?
//             tmp += world->a_vertxs[i * (size) + (size - j)]->
//             pos[1], count++ : 0;
//         }
//     }
//     if (count == 0)
//         return;
//     tmp /= count;
//     for (int i = x - world->s_br; i < x + world->s_br; i++) {
//         if (i < 0 || i >= size)
//             continue;
//         for (int j = y - world->s_br; j < y + world->s_br; j++) {
//             ((size - j) >= 0 && (size - j) < (size)) ?
//             (world->a_vertxs[i * (size) + (size - j)]->
//             pos[1] = (world->a_vertxs[i * (size) + (size - j)]->
//             pos[1] + tmp) / 2): 0;
//         }
//     }
// }

void average_d_br(minimap_t *map, world_t *world, sfVector2i pos, int size)
{
    float nb = map->size.y / (float)(size);
    int x = (int)(round(pos.x / nb));
    int y = (int)(round(pos.y / nb));
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
