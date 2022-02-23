/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** my
*/

#ifndef __PROTO__
    #define __PROTO__

    #include <math.h>
    #include <time.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <stddef.h>
    #include <stdarg.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <SFML/System/Types.h>
    #include <SFML/Window/Keyboard.h>
    #include "params.h"
    #include "window.h"
    #include "mat4x4.h"
    #include "mesh.h"
    #include "list.h"
    #include "my.h"

    #define PI 3.14159265359

    #define ABS(nb) (nb) < 0 ? -(nb) : (nb)


typedef struct world_struct {
    VecSort_t *sortBuffer;
    VecSort_t *sortBuffer2;
    Mat4x4 *matrix;
    sfClock *clock;
    list_t **meshes;
    list_t **vertxs;
    list_t **triangles;
    vertex_t **a_vertxs;
    triangle_t **a_triangles;
    size_t nb_vertxs;
    size_t nb_meshes;
    size_t nb_trig;
    float p_pos[3];
    float p_dir[3];
    float *light_start;
    float *light_source;
    void (*destroy)(struct world_struct *world);
} world_t;

void move(Mat4x4 **matWorld);
void radixSortObjInt(void *toSort2, size_t sizes[2],
size_t offset_in_struct, void *buffer2);
world_t *create_world();
void add_mesh(world_t *world, mesh_t *mesh);
void draw_meshes(world_t *world, win_t *win);
vertex_t *project_meshes(world_t *world);
VecSort_t *sort_vertxs(world_t *world, vertex_t *vertxs);
list_t *get_from_index(list_t **begin, size_t index, size_t len_list);
void get_player_pos(world_t *world);
void get_player_dir(world_t *world);
mesh_t *load_from_file(char *file);
void add_player_pos(vertex_t *vertxs, size_t i, world_t *world, float *tmp);
float apply_shades(world_t *world, triangle_t *tri);
float get_direction(vertex_t *pts);
void set_light_source(world_t *world, float x, float y, float z);
void move_light(world_t *world, win_t *win);
void draw_light(world_t *world, win_t *win);
void convert_to_array(world_t *world);
void create_map(world_t *world, size_t size);
float apply_perlin(float x, float y);

#endif
