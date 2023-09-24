#include "ball.h"

// Función para inicializar una pelota
void init_ball(ball_t *ball, int x, int y, int w, int h, int dx, int dy)
{
    ball->x = x;
    ball->y = y;
    ball->w = w;
    ball->h = h;
    ball->dx = dx;
    ball->dy = dy;
}