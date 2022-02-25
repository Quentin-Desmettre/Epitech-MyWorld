/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** fps.c
*/

#include "world.h"
#include "my.h"

// C program for implementation of ftoa()
#include <math.h>
#include <stdio.h>
  
// Reverses a string 'str' of length 'len'
void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
  
// Converts a given integer x to string str[]. 
// d is the number of digits required in the output. 
// If d is more than the number of digits in x, 
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
  
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
  
    reverse(str, i);
    str[i] = '\0';
    return i;
}
  
// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
  
    // Extract floating part
    float fpart = n - (float)ipart;
  
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
  
    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot
  
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
  
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

void append(char **str, char *buf, int is_free)
{
    char *tmp = *str;
    int len = my_strlen(tmp) + my_strlen(buf);
    char *new = malloc(sizeof(char) * (len + 1));

    my_strcpy(new, tmp);
    my_strcat(new, buf);
    new[len] = '\0';
    if (is_free)
        free(tmp);
    *str = new;
}

void init_graph(sfClock **c, sfText **t, win_t *w)
{
    if (!(*t)) {
        *c = sfClock_create();
        *t = sfText_create();
        sfText_setFont(*t, sfFont_createFromFile("src/menus/minecraft.ttf"));
    }
    sfText_setCharacterSize(*t, 800 / 30.0);
    sfText_setPosition(*t, (sfVector2f){1600 * 0.8, 0});
}

void draw_fps(win_t *w)
{
    static sfClock *c = NULL;
    static sfText *t = NULL;
    static sfTime last_time = {0};
    float fps;
    char *fps_str = malloc(7);

    init_graph(&c, &t, w);
    fps = 1000000.0 /
    (sfClock_getElapsedTime(c).microseconds - last_time.microseconds);
    ftoa(fps, fps_str, 2);
    last_time = sfClock_getElapsedTime(c);
    append(&fps_str, " FPS", 1);
    if (sfClock_getElapsedTime(c).microseconds > 500000) {
        sfText_setString(t, fps_str);
        sfClock_restart(c);
    } else
        free(0);
    sfRenderWindow_drawText(w->window, t, NULL);
}
