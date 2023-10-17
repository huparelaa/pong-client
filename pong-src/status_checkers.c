#include <stdlib.h>
#include <stdio.h>
#include "ball.h"
#include "paddle.h"
#include "../globals.h"
// if return 1 collision detected else return 0
int check_collision(ball_t ball, paddle_t paddle)
{
    int left_ball, left_paddle;
    int right_ball, right_paddle;
    int top_ball, top_paddle;
    int bottom_ball, bottom_paddle;

    left_ball = ball.x;
    right_ball = ball.x + BALL_WIDTH;
    top_ball = ball.y;
    bottom_ball = ball.y + BALL_HEIGHT;

    left_paddle = paddle.x;
    right_paddle = paddle.x + PADDLE_WIDTH;
    top_paddle = paddle.y;
    bottom_paddle = paddle.y + PADDLE_HEIGHT;

    if (left_ball > right_paddle)
    {
        return 0;
    }

    if (right_ball < left_paddle)
    {
        return 0;
    }

    if (top_ball > bottom_paddle)
    {
        return 0;
    }

    if (bottom_ball < top_paddle)
    {
        return 0;
    }

    return 1;
}

void collision_handler(ball_t *ball, paddle_t paddle)
{
    // ball moving left
    if (ball->dx < 0)
    {

        ball->dx -= 1;

        // ball moving right
    }
    else
    {

        ball->dx += 1;
    }

    // change ball direction
    ball->dx = -ball->dx;

    // change ball angle based on where on the paddle it hit
    int hit_pos = (paddle.y + paddle.h) - ball->y;

    if (hit_pos >= 0 && hit_pos < 7)
    {
        ball->dy = 4;
    }

    if (hit_pos >= 7 && hit_pos < 14)
    {
        ball->dy = 3;
    }

    if (hit_pos >= 14 && hit_pos < 21)
    {
        ball->dy = 2;
    }

    if (hit_pos >= 21 && hit_pos < 28)
    {
        ball->dy = 1;
    }

    if (hit_pos >= 28 && hit_pos < 32)
    {
        ball->dy = 0;
    }

    if (hit_pos >= 32 && hit_pos < 39)
    {
        ball->dy = -1;
    }

    if (hit_pos >= 39 && hit_pos < 46)
    {
        ball->dy = -2;
    }

    if (hit_pos >= 46 && hit_pos < 53)
    {
        ball->dy = -3;
    }

    if (hit_pos >= 53 && hit_pos <= 60)
    {
        ball->dy = -4;
    }

    // ball moving right
    if (ball->dx > 0)
    {

        // teleport ball to avoid mutli collision glitch
        if (ball->x < 30)
        {

            ball->x = 30;
        }

        // ball moving left
    }
    else
    {

        // teleport ball to avoid mutli collision glitch
        if (ball->x > 600)
        {

            ball->x = 600;
        }
    }
}
