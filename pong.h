#ifndef PONG_H
#define PONG_H

void pong_init();
int init();
void update_ball(int x, int y, int dx, int dy);
void update_paddle1(int x, int y);
void update_paddle2(int x, int y);
void update_score(int score1, int score2);
void update_player(int player_number);
void update_winner(int winner_number);
void restart_game();

#endif