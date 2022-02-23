/*
** EPITECH PROJECT, 2022
** Workshop3D
** File description:
** params
*/

#ifndef PARAMS_H_
    #define PARAMS_H_

    #include "world.h"

    #define DAY 1
    #define SUN 0.8
    #define MOON 0.2
    #define IS_FILL sfTrue
    #define IS_OUTLINE sfFalse

typedef struct params_struct {
    sfBool day;
    sfBool is_fill;
    sfBool is_outline;
} params_t;

#endif
