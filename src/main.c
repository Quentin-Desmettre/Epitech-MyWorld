/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "world.h"

int main(int ac, char **av)
{
    world_t *world = create_world();
    // mesh_t *tank = load_from_file("Chicken.obj");
    srand(time(NULL));

    if (world == NULL || world->matrix == NULL)
        return 84;
    create_map(world, str_to_long(av[1]));
    // add_mesh(world, tank);
    set_light_source(world, str_to_long(av[1]) / 2, 0, 999);
    convert_to_array(world);
    world->sortBuffer = malloc(sizeof(VecSort_t) * world->nb_trig);
    world->sortBuffer2 = malloc(sizeof(VecSort_t) * world->nb_trig);
    win_t *win = win_create(world->nb_trig);
    while (win->is_open(win)) {
        move(&world->matrix);
        draw_meshes(world, win);
        win->display(win);
        while (win->poll_event(win)) {
            if (win->event.type == sfEvtClosed) {
                win->destroy(win);
                world->destroy(world);
                return 0;
            } else
                params(win);
        }
    }
}
