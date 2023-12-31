##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC = \
	./src/help.c 							\
	./src/menus/game/put_fullscreen.c 		\
	./src/mini_map/comparators.c 			\
	./src/mini_map/where.c		 			\
	./src/sounds/create_sounds.c			\
	./src/srand.c 							\
	./src/menus/map_select/double_click.c   \
	./src/menus/save_from_file.c			\
	./src/menus/spectator.c 				\
	./src/my_memset.c 						\
	./src/menus/global_win/textures.c 		\
	./src/menus/game/buttons/actions.c 		\
	./src/menus/game/accessors.c 			\
	src/menus/game/buttons/other_actions.c  \
	./src/world/background.c				\
	./src/map/refresh.c						\
	./src/menus/game/buttons/create.c		\
	./src/menus/game/buttons/events.c		\
	./src/menus/game/draw.c					\
	./src/menus/map_select/events.c 		\
	./src/menus/game/buttons/static_event.c \
	./src/menus/map_select/draw.c			\
	./src/menus/map_select/load_entries.c 	\
	./src/menus/map_select/release.c		\
	./src/fps.c                             \
	./src/free_lists.c                      \
	./src/mesh/draw.c                       \
	./src/map/perlin.c                      \
	./src/map/smooth.c                      \
	./src/brush/brush.c                     \
	./src/brush/brush_next.c                \
	./src/mesh/create.c                     \
	./src/radix/utils.c                     \
	./src/input/params.c                    \
	./src/light/shades.c                    \
	./src/world/create.c                    \
	./src/matrix/mat4x4.c                   \
	./src/menus/globals.c                   \
	./src/mini_map/draw.c                   \
	./src/world/convert.c                   \
	./src/input/movement.c                  \
	./src/map/create_map.c                  \
	./src/mesh/calculate.c                  \
	./src/menus/strconcat.c                 \
	./src/window/win_draw.c                 \
	./src/light/draw_light.c                \
	./src/list/append_node.c                \
	./src/list/remove_node.c                \
	./src/menus/main/scale.c                \
	./src/map/smooth_shader.c               \
	./src/matrix/mat_create.c               \
	./src/matrix/mat_invert.c               \
	./src/menus/game/create.c               \
	./src/menus/game/events.c               \
	./src/mini_map/mini_map.c               \
	./src/window/win_create.c               \
	./src/matrix/mat_create2.c              \
	./src/menus/button/button.c             \
	./src/menus/settings/load.c             \
	./src/menus/settings/save.c             \
	./src/menus/slider/create.c             \
	./src/menus/slider/events.c             \
	./src/menus/main/main_menu.c            \
	./src/menus/settings/apply.c            \
	./src/menus/slider/destroy.c            \
	./src/menus/global_win/main.c           \
	./src/menus/line_edit/create.c          \
	./src/menus/line_edit/events.c          \
	./src/menus/settings/destroy.c          \
	./src/menus/settings/set_evt.c          \
	./src/menus/map_create/create.c         \
	./src/menus/map_select/create.c         \
	./src/menus/settings/checkbox.c         \
	./src/menus/settings/settings.c         \
	./src/menus/map_create/release.c        \
	./src/menus/settings/sound_evt.c        \
	./src/menus/sprite/init_sprite.c        \
	./src/menus/sprite/sprite_modif.c       \
	./src/menus/button/get_button_ev.c      \
	./src/menus/global_win/transition.c     \
	./src/menus/settings/visu_updates.c     \
	./src/menus/global_win/init_window.c    \
	./src/menus/global_win/rescale_all.c    \
	./src/menus/map_create/events_ptrs.c    \
	./src/menus/settings/move_settings.c    \
	./src/menus/settings/rendering_evt.c    \
	./src/menus/settings/scale_settings.c   \
	./src/menus/settings/set_evt_manager.c	\
	./src/save.c							\
	./src/mouse_move/mouse_move.c			\
	./src/player/calc.c

OBJ = $(SRC:.c=.o)

NAME = my_world

CFLAGS = -Wall -Wextra -I ./include/ -g

LDFLAGS += -L lib/my/ -lmy -g -lm 										\
		-lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window 	\
		-Wparentheses -Wsign-compare -Wpointer-sign -Wuninitialized 	\
		-Wunused-but-set-variable -g

all: $(NAME)

$(NAME):   $(OBJ)
	make -s -C lib/my/
	gcc -o $(NAME) $(FLAGS) $(OBJ) $(LDFLAGS)

clean:
	find . -name "*.o" -delete
	rm -f $(OBJ)

fclean:    clean
	rm -f $(NAME)
	rm -f *.c~
	rm -f *.out
	rm -f vgcore*
	rm -f *.gcda
	rm -f *.gcno
	rm -f unit_tests*

re:        fclean all

run: all
	./$(NAME)

lib_fclean:
		cd lib/my/ && make fclean

push_fclean: fclean
		cd lib/my/ && make fclean

re:	fclean all

valgrind: all
	valgrind --track-origins=yes --leak-check=full \
	--show-leak-kinds=definite,indirect ./$(NAME)

tests_run: exec_lib
	gcc -o unit_tests $(SRC) tests/*.c -Llib/ -lmy --coverage -lcriterion
	./unit_tests
	gcovr --exclude tests
	gcovr -b --exclude tests
