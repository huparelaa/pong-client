#include "paddle.h"
#ifndef BALL_H
#define BALL_H

// Definición de la estructura ball_t
typedef struct {
    int x, y; // posición en la pantalla
    int w, h; // ancho y alto de la pelota
    int dx, dy; // vector de movimiento
} ball_t;

void ball_updater(ball_t *ball, int x, int y, int dx, int dy);

void move_ball(ball_t *ball, int h, int w, paddle_t paddle, int player);

#endif
