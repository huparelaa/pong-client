#include "ball.h"
#include "status_checkers.h"
#include "paddle.h"
#include "../pong_info_sender.h"
#include <stdio.h>
#include "../pong.h"

extern int able_to_send_score;
// Función para inicializar una pelota
void ball_updater(ball_t *ball, int x, int y, int dx, int dy)
{
    ball->x = x;
    ball->y = y;
    ball->dx = dx;
    ball->dy = dy;
}

// Mover la pelota
void move_ball(ball_t *ball, int h, int w, paddle_t paddle, int player)
{
    player = player;
    ball->x += ball->dx;
    ball->y += ball->dy;
    if (able_to_send_score)
    {
        if (player == 0)
        {
            if (ball->x > w - 10)
            {
                player_scored(1);
                able_to_send_score = 0;
            }
        }
        else if (player == 1)
        {
            if (ball->x < 0)
            {
                player_scored(2);
                able_to_send_score = 0;
            }
        }
    }

    if (ball->y < 0 || ball->y > h - 10)
    {
        ball->dy = -ball->dy;
    }
}
