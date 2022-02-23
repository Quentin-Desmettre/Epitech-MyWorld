##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## makefile
##

SRC = 	src/matrix/mat4x4.c 		\
	 	src/matrix/mat_invert.c 	\
		src/matrix/mat_create.c 	\
		src/matrix/mat_create2.c 	\
		src/list/append_node.c		\
		src/list/remove_node.c		\
		src/window/win_create.c		\
		src/window/win_draw.c		\
		src/input/movement.c		\
		src/input/params.c			\
		src/world/create.c			\
		src/world/convert.c			\
		src/light/shades.c			\
		src/light/draw_light.c		\
		src/mesh/calculate.c		\
		src/mesh/create.c			\
		src/mesh/draw.c				\
		src/player/calc.c			\
		src/map/create_map.c		\
		src/map/perlin.c			\
		src/load.c					\
		src/utils.c

NAME = my_world

CC = cc -Iinclude

OBJ = $(SRC:.c=.o)

FLAGS = -g -lm -lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window \
		-Wparentheses -Wsign-compare -Wpointer-sign -Wuninitialized \
		-Wunused-but-set-variable -lstdc++

MY	=	my.h

all: exec_lib $(NAME)

exec_lib:
	cd lib/my/ && make

clean:
	rm -f $(OBJ)

$(NAME):
	gcc -o $(NAME) src/main.c $(SRC) -Llib/ -lmy -Iinclude $(FLAGS)

run: re
	./$(NAME) 64

fclean: clean
	rm -f $(NAME)
	rm -f *.c~
	rm -f *.out
	rm -f vgcore*
	rm -f *.gcda
	rm -f *.gcno
	rm -f unit_tests*

lib_fclean:
		cd lib/my/ && make fclean

push_fclean: fclean
		cd lib/my/ && make fclean

re:	fclean all

valgrind: all
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=definite \
	./$(NAME) 64

tests_run: exec_lib
	gcc -o unit_tests $(SRC) tests/*.c -Llib/ -lmy --coverage -lcriterion
	./unit_tests
	gcovr --exclude tests
	gcovr -b --exclude tests
