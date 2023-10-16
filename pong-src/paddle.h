#ifndef PADDLE_H
#define PADDLE_H

// Definición de la estructura paddle_t
typedef struct {
    int x, y; // posición en la pantalla
    int w, h; // ancho y alto de la paleta
    int dy; // vector de movimiento
} paddle_t;

void move_paddle(paddle_t *paddle, int height, int d);
void paddle1_updater(paddle_t *paddle, int x, int y);
void paddle2_updater(paddle_t *paddle, int x, int y);


#endif
