##
## EPITECH PROJECT, 2021
## B-MUL-200-LIL-2-1-myworld-paulin.leclercq
## File description:
## Makefile
##

SRC = 	*.c \
		*/*.c

SFML = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

MY_LIB = -L ../lib/my/

CFLAGS = -Wall -Wextra -g

INCLUDES = -I ./

NAME = a.out

all:
	gcc $(CFLAGS) $(SRC) $(INCLUDES) $(SFML) $(MY_LIB)
