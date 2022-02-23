/*
** EPITECH PROJECT, 2022
** mesh.h
** File description:
** mesh
*/

#ifndef MESH_H_
    #define MESH_H_

    #include "world.h"

typedef struct vecsort {
    void *data;
    int id;
} vecsort_t;

typedef struct vertex {
    float pos[3];
} vertex_t;

typedef struct triangle {
    int vertxs[3];
    sfColor color;
    vertex_t *ptrs[3];
    void *mesh_ptr;
} triangle_t;

typedef struct mesh {
    triangle_t *trig;
    size_t trig_size;
    vertex_t *vertxs;
    size_t nb_vertxs;
    sfBool is_selected;
} mesh_t;

mesh_t *create_mesh(size_t nb_vertxs, vertex_t *mesh_vertxs,
size_t trig_size, ...);
void draw_triangle(vertex_t vertxs[3], sfColor color, win_t *win,
sfBool is_selected, float direction);
void center_vertxs(vertex_t *vertxs, sfColor *color,
float direction, sfBool day);

#endif
