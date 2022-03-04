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
    unsigned long s = size * size;
    char *path = str_concat(2, "./map/", filename);
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC,
    ALL_FLAGS);

    write(fd, &size, sizeof(unsigned int));
    for (unsigned long i = 0; i < s; i++)
        write(fd, &(world->a_vertxs[i]->pos[1]), sizeof(float));
    close(fd);
    free(path);
}

long read_all_file(int fd)
{
    long tmp;
    long size = 0;
    char buf[30000];

    while (1) {
        tmp = read(fd, buf, 30000);
        if (tmp < 0) {
            close(fd);
            return -1;
        }
        if (!tmp)
            break;
        size += tmp;
    }
    close(fd);
    return size;
}

bool is_file_valid(char const *file)
{
    int fd = open(file, O_RDONLY);
    long size = 0;
    unsigned map_size;
    char buf[30000];
    int tmp;

    if (fd < 0)
        return false;
    if (read(fd, &map_size, sizeof(unsigned)) != sizeof(unsigned)) {
        close(fd);
        return false;
    }
    size = read_all_file(fd);
    if (size < 0)
        return false;
    tmp = (size == (map_size * map_size * sizeof(float)));
    return tmp;
}

unsigned int read_map(game_t *game, const char *filename)
{
    unsigned int size;
    world_t *world = game->world;
    char *path = str_concat(2, "./map/", filename);
    int fd = open(path, O_RDONLY);
    unsigned long s;

    read(fd, &size, sizeof(unsigned int));
    game->win->map_size = size;
    game->minimap->map_size = size;
    s = size * size;
    for (unsigned long i = 0; i < s; i++)
        read(fd, &(world->a_vertxs[i]->pos[1]), sizeof(float));
    close(fd);
    free(path);
    return size;
}
