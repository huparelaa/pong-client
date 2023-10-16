#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "pong.h"
#include "globals.h"

int buffer_parser(char *buffer)
{
    char new_buffer[BUF_SIZE];
    strcpy(new_buffer, buffer);
    char *token = strtok(new_buffer, " ");
    if (strcmp(token, BALL_UPDATER) == 0)
    {
        token = strtok(NULL, " ");
        int x = atoi(token);
        token = strtok(NULL, " ");
        int y = atoi(token);
        token = strtok(NULL, " ");
        int dx = atoi(token);
        token = strtok(NULL, " ");
        int dy = atoi(token);
        update_ball(x, y, dx, dy);
        return OK;
    }
    else if (strcmp(token, PADDLE1_UPDATER) == 0)
    {
        token = strtok(NULL, " ");
        int x = atoi(token);
        token = strtok(NULL, " ");
        int y = atoi(token);
        update_paddle1(x, y);
        return OK;
    }
    else if (strcmp(token, PADDLE2_UPDATER) == 0)
    {
        token = strtok(NULL, " ");
        int x = atoi(token);
        token = strtok(NULL, " ");
        int y = atoi(token);
        update_paddle2(x, y);
        return OK;
    }
    else if (strcmp(token, SCORE_UPDATER) == 0)
    {
        token = strtok(NULL, " ");
        int score1 = atoi(token);
        token = strtok(NULL, " ");
        int score2 = atoi(token);
        update_score(score1, score2);
        return OK;
    }
    else if (strcmp(token, NUMBER_PLAYER) == 0)
    {
        token = strtok(NULL, " ");
        int player = atoi(token);
        update_player(player);
        return OK;
    }
    else
        return SYSERR; // No es un mensaje de actualización
}