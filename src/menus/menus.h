/*
** EPITECH PROJECT, 2022
** my world
** File description:
** menu.h
*/

#ifndef MENU_H
    #define MENU_H

    #define BACKGROUND_FRAMES 1

    #include <stdlib.h>
    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/System.h>

    #define true 1
    #define false 0
    #define bool int

    #define FONT "pusab.otf"
    #define TEXTURE "truc.png"

    #define GROW_FACTOR 1.05
    #define MAIN_MENU_TXT_FACTOR 0.7

static const sfIntRect button_rect = {
    1, 1, 1, 1
};

static const sfIntRect main_background_rects[BACKGROUND_FRAMES] = {
    {0, 0, 1, 1}
};

// size factors
static const float main_buts_sf[4][2] = {
    {0.7, 0.12}, {0.7, 0.12}, {0.33, 0.12}, {0.33, 0.12}
};
// pos factors
static const float main_buts_pf[4][2] = {
    {0.5, 0.4}, {0.5, 0.6}, {0.313, 0.8}, {0.687, 0.8}
};

typedef struct win {
    int state;
    int next_state;
    bool is_transition;

    void *map_select;
    void *settings;
    void *create_level;
    void *how_to_play;
    void *home;
    void *game;

    const sfTexture* (*draw[6])(void *);
    void (*event[6])(struct win *, sfEvent ev);
    void (*update[6])(void *);

    sfClock *lum_clock;

    sfRenderWindow *win;
} window_t;

typedef struct {
    sfText *text;
    sfSprite *sprite;
    int is_press;
    int is_hover;
    sfVector2f pos;
    sfVector2f size;
    void (*action)(window_t *);
} button_t;

typedef enum {
    HOME, MAP_SELECT, SETTINGS, CREATE_MAP,
    HOW_TO_PLAY, EDIT_MAP, EXIT
} state_t;

typedef struct {
    button_t *buttons[4];
    sfSprite *background;
    sfRenderTexture *text;
} main_menu_t;

void factor_color(sfSprite *s, float factor);
void hover_button(button_t *b, int is_on);
void press_button(button_t *b, int is_press);
sfFont *global_font(void);
sfTexture *global_texture(void);
sfSprite *init_sprite_from_texture(sfTexture const *t);
sfText *init_text(char const *str, int charSize);
void set_sprite_size(sfSprite *s, sfVector2f size);
sfSprite *init_sprite(sfTexture *t, sfIntRect rect, sfVector2f size);
button_t *init_button(sfTexture *t, sfIntRect rect, sfVector2f pos,
sfVector2f size, char const *str, void (*action)(window_t *));
bool is_on_button(sfVector2f pos, button_t *b);
void check_button_move(button_t **buttons, int nb_button, sfEvent move);
void check_button_press(button_t **buttons, int nb_button, sfEvent press);
int button_at(button_t **buttons, int nb_button, sfEvent release);
void set_next_win_state(window_t *win, int next);
void main_menu_release(main_menu_t *m, sfEvent ev, window_t *win);
void main_menu_event(window_t *win, sfEvent ev);
sfVector2f get_sprite_size(sfSprite *s);
void center_sprite(sfSprite *s);
void scale_main_buttons(button_t *buttons[4], sfVector2f winSize);
void move_main_buttons(button_t *buttons[4], sfVector2f winSize);
main_menu_t *init_main_menu(sfTexture *t, sfVector2f winSize);
void draw_button_to_rtex(button_t *b, sfRenderTexture *rtex);
const sfTexture *draw_main_menu(main_menu_t *menu);
window_t *win_create(void);
void destroy_home(main_menu_t *menu);
void win_destroy(window_t *win);
void switch_color_dir(window_t *win, int *dir);
void reset_lum(window_t *win, int *dir, sfColor *lum);
void update_lum(sfColor *lum, int *fac);
void update_transition(window_t *win, sfSprite *s);
void draw(window_t *win);
void poll_events(window_t *win);
int main(void);
void center_text(sfText *t);

#endif
