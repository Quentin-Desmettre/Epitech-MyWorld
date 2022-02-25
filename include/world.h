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
    #define CONST 0b10000000

    #define ABS(nb) (nb) < 0 ? -(nb) : (nb)

typedef struct world_struct {
    vecsort_t *sortBuffer;
    vecsort_t *sortBuffer2;
    mat4x4 *matrix;
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
    int s_br;
} world_t;

typedef struct tmp_struct {
    world_t *world;
    size_t size;
    long line;
    long col;
    size_t end;
    size_t start;
    sfBool turn;
} tmp_shadow_t;

static const float height = 800.0;

void move(mat4x4 **mat_world);
void radix_sort(void *toSort2, size_t sizes[2],
size_t offset_in_struct, void *buffer2);
world_t *create_world();
void add_mesh(world_t *world, mesh_t *mesh);
void draw_meshes(world_t *world, win_t *win);
vertex_t *project_meshes(world_t *world);
vecsort_t *sort_vertxs(world_t *world, vertex_t *vertxs);
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
void create_minimap(world_t *world, win_t *win, long long size);
sfColor center_vertxs(vertex_t *vertxs, triangle_t *tri,
world_t *world, win_t *win);
void params(win_t *win, world_t *world);
void rota_right(world_t *world, win_t *win);
void rota_left(world_t *world, win_t *win);
void change_color(mesh_t *mesh, size_t size, size_t i, size_t j);
void smooth(mesh_t *mesh, size_t size);
void smooth_shadow(world_t *world, win_t *win);
sfBool is_out(size_t max, size_t size, long i, long j);
void up_br(world_t *world, win_t *win, sfVector2i pos);
void down_br(world_t *world, win_t *win, sfVector2i pos);
void free_mesh(void *value);

#endif
