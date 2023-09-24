
// Using libs SDL, glibc
#include <SDL.h> //SDL version 2.0
#include <stdlib.h>
#include <stdio.h>
#include "ball.h"
#include "paddle.h"
#include "drawers.h"
#include "status_checkers.h"
#include "init.h"
#define SCREEN_WIDTH 640  // window height
#define SCREEN_HEIGHT 480 // window width

// function prototypes
// initilise SDL
int init(int w, int h, int argc, char *args[]);

// Program globals
static ball_t ball;
static paddle_t paddle[2];
int score[] = {0, 0};
int width, height; // used if fullscreen
int MAX_SCORE = 5;

SDL_Window *window = NULL; // The window we'll be rendering to
SDL_Renderer *renderer;	   // The renderer SDL will use to draw to the screen

// surfaces
static SDL_Surface *screen;
static SDL_Surface *title;
static SDL_Surface *numbermap;
static SDL_Surface *end;

// textures
SDL_Texture *screen_texture;

int main(int argc, char *args[])
{

	// SDL Window setup
	if (init(SCREEN_WIDTH, SCREEN_HEIGHT, argc, args) == 1)
	{

		return 0;
	}

	SDL_GetWindowSize(window, &width, &height);

	int sleep = 0;
	int quit = 0;
	int state = 0;
	int r = 0;
	Uint32 next_game_tick = SDL_GetTicks();

	// Initialize the ball position data.
	init_game(&ball, paddle, screen->h, screen->w);

	// render loop
	while (quit == 0)
	{

		// check for new events every frame
		SDL_PumpEvents();

		const Uint8 *keystate = SDL_GetKeyboardState(NULL);

		if (keystate[SDL_SCANCODE_ESCAPE])
		{

			quit = 1;
		}

		if (keystate[SDL_SCANCODE_UP])
		{

			move_paddle(&paddle[1], screen->h, 1);
		}

		if (keystate[SDL_SCANCODE_DOWN])
		{

			move_paddle(&paddle[1], screen->h, 0);
		}

		if (keystate[SDL_SCANCODE_W])
		{
			move_paddle(&paddle[0], screen->h, 1);
		}

		if (keystate[SDL_SCANCODE_S])
		{
			move_paddle(&paddle[0], screen->h, 0);
		}

		// draw background
		SDL_RenderClear(renderer);
		SDL_FillRect(screen, NULL, 0x000000ff);

		// display main menu
		if (state == 0)
		{

			if (keystate[SDL_SCANCODE_SPACE])
			{

				state = 1;
			}

			draw_menu(screen, title);

		}
		else if (state == 2)
		{

			if (keystate[SDL_SCANCODE_SPACE])
			{
				state = 0;
				// delay for a little bit so the space bar press dosnt get triggered twice
				// while the main menu is showing
				SDL_Delay(500);
			}

			if (r == 1)
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
		else if (state == 1)
		{

			// check score
			r = check_score(MAX_SCORE, score);

			// if either player wins, change to game over state
			if (r == 1)
			{

				state = 2;
			}
			else if (r == 2)
			{

				state = 2;
			}

			//* Move the balls for the next frame.
			move_ball(&ball, paddle, screen->h, screen->w, score);

			// draw net
			draw_net(screen);

			// draw paddles
			draw_paddle(screen, paddle);

			//* Put the ball on the screen.
			draw_ball(screen, &ball);

			// draw the score
			draw_player_score(screen, numbermap, score[0], 1);
			draw_player_score(screen, numbermap, score[1], 2);
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
