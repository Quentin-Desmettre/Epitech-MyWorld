/*
** EPITECH PROJECT, 2022
** utils.c
** File description:
** utils
*/

#include "world.h"

//template <class T, class int>
void radixSortObjInt(void *toSort2, size_t type_size, size_t size, size_t offset_in_struct, void *buffer2) {
    uint8_t *toSort = toSort2;
    uint8_t *buffer = buffer2;
    int const buftype = 8;
    int const bufsize = pow(2, buftype);

    //if (std::is_signed<int>())
        for (size_t x = 0; x < size; x++)
            *(toSort+x*type_size+offset_in_struct+sizeof(int)-1) ^= 0b10000000;

    int counts[bufsize+1];
    for (size_t i = 0; i < sizeof(int); i++) {
        memset(counts, 0, sizeof(counts));

        // counts bits
        for (size_t x = 0; x < size; x++)
            counts[*(toSort+x*type_size+offset_in_struct+i)+1]++;

        // some counts
        for (int x = 1; x < bufsize; x++)
            counts[x] += counts[x-1];


        // place in bucket
        for (size_t x = 0; x < size; x++) {
            memcpy(buffer + type_size*counts[*(toSort+x*type_size+offset_in_struct+i)]++, toSort+x*type_size, type_size);
        }

        uint8_t *tmp = toSort;
        toSort = buffer;
        buffer = tmp;
    }

    if (sizeof(int) % 2)
        memcpy(buffer, toSort, size*type_size);

    //if (std::is_signed<int>())
        for (size_t x = 0; x < size; x++)
            *(((uint8_t *)(toSort+(x*type_size)))+offset_in_struct+sizeof(int)-1) ^= 0b10000000;
}