#include <string.h>

// ROOMS
#define MAX_CLIENTS 2
#define MAX_ROOMS 10
#define USERNAME_LEN 32
#define MAX_MESSAGE_LENGTH 256
#define BUF_SIZE 1024

//GLOBAL VARIABLES
#define TRUE 1
#define FALSE 0
#define SYSERR -1
#define OK 0

//SERVER
#define PORT 3001
#define IP "3.145.191.38"
//#define IP "127.0.0.1"

//ACTIONS
#define ERROR "error\n"
#define CLOSE "/close\n"
#define EXIT "exit\n"
#define USERNAMExMESSAGE ": "
#define START "game started\n"
#define END "end_game\n"

// Colors
#define NCOLORS 12
#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE   "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN   "\x1B[36m"
#define LRED   "\x1B[91m"
#define LGREEN   "\x1B[92m"
#define LYELLOW   "\x1B[93m"
#define LBLUE   "\x1B[94m"
#define LMAGENTA  "\x1B[95m"
#define LCYAN   "\x1B[96m"
#define WHITE  "\x1B[37m"
#define RESET "\x1B[0m"

// PONG VARIABLES
#define SCREEN_WIDTH 640  // window height
#define SCREEN_HEIGHT 480 // window width

// PONG UPDATERS
#define BALL_UPDATER "BALL:"
#define PADDLE1_UPDATER "PADDLE1:"
#define PADDLE2_UPDATER "PADDLE2:"
#define SCORE_UPDATER "SCORE:"
#define NUMBER_PLAYER "PLAYER:"
#define GAME_OVER "WINNER:"
#define CLOSE_GAME "CLOSE"
#define RESTART "RESTART"

// PONG SENDER FLAGS
#define SCORE_SENDER_1 "1SCORED"
#define SCORE_SENDER_2 "2SCORED"

// PONG DIMENSIONS
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 50
#define BALL_WIDTH 10
#define BALL_HEIGHT 10