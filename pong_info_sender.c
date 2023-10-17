#include "pong_info_sender.h"
#include "globals.h"
#include <stdio.h>
#include <arpa/inet.h>


extern int sockfd;

void send_paddle_position(int x, int y, int player)
{
    char send_buffer[BUF_SIZE];
    sprintf(send_buffer, "PADDLE%d: %d %d", player, x, y);
    // send message to server
    if (send(sockfd, send_buffer, strlen(send_buffer), 0) == SYSERR)
    {
        perror("paddle sending");
    }
}

void player_scored(int player){
    char send_buffer[BUF_SIZE];
    if(player == 1){
        sprintf(send_buffer, "%s", SCORE_SENDER_1);
    }else if(player == 2){
        sprintf(send_buffer, "%s", SCORE_SENDER_2);
    }
    // send message to server
    if (send(sockfd, send_buffer, strlen(send_buffer), 0) == SYSERR)
    {
        perror("score sending");
    }
}

void send_ball_position(int x, int y, int dx, int dy){
    char send_buffer[BUF_SIZE];
    sprintf(send_buffer, "%s %d %d %d %d", BALL_UPDATER, x, y, dx, dy);
    // send message to server
    if (send(sockfd, send_buffer, strlen(send_buffer), 0) == SYSERR)
    {
        perror("ball sending");
    }
}