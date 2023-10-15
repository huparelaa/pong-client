#include <SDL.h>
#include "ball.h"
#ifndef DRAWERS_H
#define DRAWERS_H

void draw_menu(SDL_Surface *screen, SDL_Surface *title);
void draw_net(SDL_Surface *screen);
void draw_ball(SDL_Surface *screen, ball_t *ball);
void draw_player_score(SDL_Surface *screen, SDL_Surface *numbermap, int score, int player_number);
void draw_paddle(SDL_Surface *screen, paddle_t paddle[2]);

#endif