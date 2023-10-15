#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "paddle.h"

// función para modificar la posición de la paleta
void paddle1_updater(paddle_t *paddle, int x, int y)
{
    paddle->x = x;
    paddle->y = y;
}

void paddle2_updater(paddle_t *paddle, int x, int y)
{
    paddle->x = x;
    paddle->y = y;
}

// Función para mover una paleta
// void move_paddle(paddle_t *paddle, int height, int d)
// {
//     if (d == 0)
//     {
//         if (paddle->y >= height - paddle->h)
//         {
//             paddle->y = height - paddle->h;
//         }
//         else
//         {
//             paddle->y += 5;
//         }
//     }
//     if (d == 1)
//     {
//         if (paddle->y <= 0)
//         {
//             paddle->y = 0;
//         }
//         else
//         {
//             paddle->y -= 5;
//         }
//     }
// }
