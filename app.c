#include <SDL.h> //SDL version 2.0
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "game_status.h"
#include "ball.h"
#include "paddle.h"
#include "drawers.h"
#include "protocole.h"
#define SCREEN_WIDTH 640  // window height
#define SCREEN_HEIGHT 480 // window width
int width;
int height;

int init(int width, int height, int argc, char *args[]);

game_status game;
int commands[] = {0, 0, 0, 0, 0};
// commands description
/*
commands[0] - up1
commands[1] - down1
commands[2] - up2
commands[3] - down2
commands[4] - start
commands[5] - exit

*/

SDL_Window *window = NULL; // The window we'll be rendering to
SDL_Renderer *renderer;	   // The renderer SDL will use to draw to the screen

// surfaces
static SDL_Surface *screen;
static SDL_Surface *title;
static SDL_Surface *numbermap;
static SDL_Surface *end;

SDL_Texture *screen_texture;
// creamos una función para enviar inputs y recibir el estado del juego


int main(int argc, char *args[])
{

	// socket setUp
	char *ip = "127.0.0.1";
	int port = 3001;
	int sockfd;
	struct sockaddr_in addr;
	char buffer[1024];
	socklen_t addr_size;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	// obtenemos el estado inicial del juego
	sendto(sockfd, "FIRST", 1024, 0, (struct sockaddr *)&addr, sizeof(addr));
	recvfrom(sockfd, &game, sizeof(game), 0, (struct sockaddr *)&addr, &addr_size);

	// SDL Window setup
	if (init(SCREEN_WIDTH, SCREEN_HEIGHT, argc, args) == 1)
	{

		return 0;
	}

	SDL_GetWindowSize(window, &width, &height);

	int sleep = 0;
	Uint32 next_game_tick = SDL_GetTicks();

	// Initialize the ball position data.
	while (game.status != 2)
	{
		
		printf("up1:%d down1:%d up2:%d down2:%d start:%d exit:%d\n", commands[0], commands[1], commands[2], commands[3], commands[4], commands[5]);
		
		game = stablish_communication(sockfd, commands, addr);
		//ball position
		printf("ball x:%d y:%d\n", game.ball.x, game.ball.y);
		//paddle position
		printf("paddle1 x:%d y:%d\n", game.paddles[0].x, game.paddles[0].y);
		printf("paddle2 x:%d y:%d\n", game.paddles[1].x, game.paddles[1].y);
		//score
		printf("score1:%d score2:%d\n", game.score[0], game.score[1]);
		//status
		printf("status:%d\n", game.status);
		//r
		printf("r:%d\n", game.r);
		

		// check for new events every frame
		SDL_PumpEvents();

		const Uint8 *keystate = SDL_GetKeyboardState(NULL);

		if (keystate[SDL_SCANCODE_ESCAPE])
		{
			commands[5] = 1;
		}
		else
		{
			commands[5] = 0;
		}

		if (keystate[SDL_SCANCODE_UP])
		{

			commands[0] = 1;
		}
		else
		{
			commands[0] = 0;
		}

		if (keystate[SDL_SCANCODE_DOWN])
		{

			commands[1] = 1;
		}
		else
		{
			commands[1] = 0;
		}

		if (keystate[SDL_SCANCODE_W])
		{
			commands[2] = 1;
		}
		else
		{
			commands[2] = 0;
		}

		if (keystate[SDL_SCANCODE_S])
		{
			commands[3] = 1;
		}
		else
		{
			commands[3] = 0;
		}

		// draw background
		SDL_RenderClear(renderer);
		SDL_FillRect(screen, NULL, 0x000000ff);

		// display main menu
		if (game.status == 0)
		{

			if (keystate[SDL_SCANCODE_SPACE])
			{

				commands[4] = 1;
			}
			else
			{
				commands[4] = 0;
			}

			draw_menu(screen, title);
		}
		else if (game.status == 2)
		{

			if (keystate[SDL_SCANCODE_SPACE])
			{
				commands[4] = 1;
				// delay for a little bit so the space bar press dosnt get triggered twice
				// while the main menu is showing
				SDL_Delay(500);
			}
			else
			{
				commands[4] = 0;
			}

			if (game.r == 1)
			{

				// if player 1 is AI if player 1 was human display the return value of r not 3
				draw_game_over(1, screen, end);
			}
			else
			{

				// display gameover
				draw_game_over(2, screen, end);
			}

			// display the game
		}
		else if (game.status == 1)
		{
			// draw net
			draw_net(screen);

			// draw paddles
			draw_paddle(screen, game.paddles);

			//* Put the ball on the screen.
			draw_ball(screen, &game.ball);

			// draw the score
			draw_player_score(screen, numbermap, game.score[0], 1);
			draw_player_score(screen, numbermap, game.score[1], 2);
		}
		SDL_UpdateTexture(screen_texture, NULL, screen->pixels, screen->w * sizeof(Uint32));
		SDL_RenderCopy(renderer, screen_texture, NULL, NULL);

		// draw to the display
		SDL_RenderPresent(renderer);

		// time it takes to render  frame in milliseconds
		next_game_tick += 1000 / 60;
		sleep = next_game_tick - SDL_GetTicks();

		if (sleep >= 0)
		{

			SDL_Delay(sleep);
		}
	}
	// free loaded images
	SDL_FreeSurface(screen);
	SDL_FreeSurface(title);
	SDL_FreeSurface(numbermap);
	SDL_FreeSurface(end);

	// free renderer and all textures used with it
	SDL_DestroyRenderer(renderer);

	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}

int init(int width, int height, int argc, char *args[])
{

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{

		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	int i;

	for (i = 0; i < argc; i++)
	{

		// Create window
		if (strcmp(args[i], "-f"))
		{

			SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);
		}
		else
		{

			SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
		}
	}

	if (window == NULL)
	{

		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	// create the screen sruface where all the elemnts will be drawn onto (ball, paddles, net etc)
	screen = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);

	if (screen == NULL)
	{

		printf("Could not create the screen surfce! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	// create the screen texture to render the screen surface to the actual display
	screen_texture = SDL_CreateTextureFromSurface(renderer, screen);

	if (screen_texture == NULL)
	{

		printf("Could not create the screen_texture! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	// Load the title image
	title = SDL_LoadBMP("title.bmp");

	if (title == NULL)
	{

		printf("Could not Load title image! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	// Load the numbermap image
	numbermap = SDL_LoadBMP("numbermap.bmp");

	if (numbermap == NULL)
	{

		printf("Could not Load numbermap image! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	// Load the gameover image
	end = SDL_LoadBMP("gameover.bmp");

	if (end == NULL)
	{

		printf("Could not Load title image! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	// Set the title colourkey.
	Uint32 colorkey = SDL_MapRGB(title->format, 255, 0, 255);
	SDL_SetColorKey(title, SDL_TRUE, colorkey);
	SDL_SetColorKey(numbermap, SDL_TRUE, colorkey);

	return 0;
}
