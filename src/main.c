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
        if (win->event.type == sfEvtClosed) {
            win->destroy(win);
            world->destroy(world);
            return 0;
        } else
            params(win);
    }
    return 1;
}

int main(int ac, char **av)
{
    world_t *world = create_world();
    win_t *win;

    if (world == NULL || world->matrix == NULL)
        return 84;
    srand(time(NULL));
    create_map(world, str_to_long(av[1]));
    set_light_source(world, str_to_long(av[1]) / 2, 0, 999);
    convert_to_array(world);
    world->sortBuffer = malloc(sizeof(VecSort_t) * world->nb_trig);
    world->sortBuffer2 = malloc(sizeof(VecSort_t) * world->nb_trig);
    win = win_create(world->nb_trig);
    while (win->is_open(win)) {
        move(&world->matrix);
        draw_meshes(world, win);
        win->display(win);
        if (!poll_window_ev(win, world))
            return 0;
    }
}
