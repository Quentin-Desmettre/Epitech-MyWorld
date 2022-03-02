/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "world.h"
#include "menus.h"

void save_map(game_t *game, const char *filename, unsigned int size)
{
    world_t *world = game->world;
    char *map = malloc(sizeof(char) * 8);
    int fd = 0;
    unsigned long s = size * size;

    strcpy(map, "./map/");
    fd = open(str_concat(2, map, filename), O_WRONLY | O_CREAT | O_TRUNC,
    ALL_FLAGS);
    write(fd, &size, sizeof(unsigned int));
    for (unsigned long i = 0; i < s; i++)
        write(fd, &(world->a_vertxs[i]->pos[1]), sizeof(float));
}

unsigned int read_map(game_t *game, const char *filename)
{
    unsigned int size;
    world_t *world = game->world;
    char *map = malloc(sizeof(char) * 8);
    int fd = 0;
    unsigned long s;

    strcpy(map, "./map/");
    fd = open(str_concat(2, map, filename), O_RDONLY);
    read(fd, &size, sizeof(unsigned int));
    create_map(world, size);
    set_light_source(world, size / 2.0, 1, 1000);
    convert_to_array(world);
    s = size * size;
    for (unsigned long i = 0; i < s; i++)
        read(fd, &(world->a_vertxs[i]->pos[1]), sizeof(float));
    return size;
}
