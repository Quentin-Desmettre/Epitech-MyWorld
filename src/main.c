/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "world.h"

int poll_window_ev(win_t *win, world_t *world)
{
    while (win->poll_event(win)) {
        if (sfKeyboard_isKeyPressed(sfKeyAdd))
            world->size_brush++;
        if (sfKeyboard_isKeyPressed(sfKeySubtract) && world->size_brush > 0)
            world->size_brush--;
        if (win->event.type == sfEvtClosed) {
            win->destroy(win);
            world->destroy(world);
            return 0;
        } else
            params(win, world);
    }
    return 1;
}

int main(int ac, char **av)
{
    world_t *world = create_world();
    win_t *win;
    long long size = str_to_long(av[1]) + 1;

    if (world == NULL || world->matrix == NULL)
        return 84;
    srand(time(NULL));
    create_map(world, size);
    set_light_source(world, size / 2, 1, 1000);
    convert_to_array(world);
    world->sortBuffer = malloc(sizeof(vecsort_t) * world->nb_trig);
    world->sortBuffer2 = malloc(sizeof(vecsort_t) * world->nb_trig);
    win = win_create(world->nb_trig);
    win->map_size = size;
    while (win->is_open(win)) {
        move(&world->matrix);
        draw_meshes(world, win);
        create_minimap(world, win, size);
        win->display(win);
        if (!poll_window_ev(win, world))
            return 0;
    }
    return 0;
}
