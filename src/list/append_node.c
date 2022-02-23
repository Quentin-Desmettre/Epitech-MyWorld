/*
** SOLUS PROJECT, 2021
** Solus
** File description:
** append_node.c
*/

#include "list.h"
#include <stdlib.h>

list_t *get_from_index(list_t **begin, size_t index, size_t len_list)
{
    list_t *tmp = *begin;

    if (index < len_list / 2) {
        if (index % 2 == 0) {
            for (size_t i = 0; i != index; i += 2)
                tmp = tmp->next->next;
        } else if (index % 3 == 0) {
            for (size_t i = 0; i != index; i += 3)
                tmp = tmp->next->next->next;
        } else {
            for (size_t i = 0; i != index; i++)
                tmp = tmp->next;
        }
    } else {
        if ((len_list - index) % 2 == 0) {
            for (size_t i = len_list; i != index; i -= 2)
                tmp = tmp->prev->prev;
        } else if ((len_list - index) % 3 == 0) {
            for (size_t i = len_list; i != index; i -= 3)
                tmp = tmp->prev->prev->prev;
        } else {
            for (size_t i = len_list; i != index; i--)
                tmp = tmp->prev;
        }
    }
    return tmp;
}

void append_node(list_t **begin, void *data)
{
    list_t *new = malloc(sizeof(list_t));

    new->data = data;
    if (!(*begin)) {
        *begin = new;
        new->next = new;
        new->prev = new;
        return;
    }
    new->next = (*begin);
    new->prev = (*begin)->prev;
    (*begin)->prev->next = new;
    (*begin)->prev = new;
}
