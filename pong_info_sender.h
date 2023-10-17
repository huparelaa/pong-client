#ifndef PONG_INFO_SENDER_H
#define PONG_INFO_SENDER_H

void send_paddle_position(int x, int y, int player);
void player_scored(int player);
void send_ball_position(int x, int y, int dx, int dy);

#endif