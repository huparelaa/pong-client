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
        perror("send");
    }
}