#include "pong.h"
#include "globals.h"
#include "pong-src/ball.h"
#include "pong-src/paddle.h"
#include <SDL.h> //SDL version 2.0
#include "pong-src/drawers.h"
#include "pong-src/status_checkers.h"
#include "pong_info_sender.h"

int width, height; // used if fullscreen
extern int in_game;
SDL_Window *window = NULL; // The window we'll be rendering to
SDL_Renderer *renderer;    // The renderer SDL will use to draw to the screen

// surfaces
static SDL_Surface *screen;
static SDL_Surface *title;
static SDL_Surface *numbermap;
static SDL_Surface *end;

// textures
SDL_Texture *screen_texture;
int init();

// Program globals
ball_t ball;
paddle_t paddle[2];
int score[] = {0, 0};
int player = 0;
int winner = 0;

// changable variables
int sleep = 0;
int quit = 0;

void update_ball(int x, int y, int dx, int dy)
{
    ball_updater(&ball, x, y, dx, dy);
}

void update_paddle1(int x, int y)
{
    paddle1_updater(&paddle[0], x, y);
}

void update_paddle2(int x, int y)
{
    paddle2_updater(&paddle[1], x, y);
}

void update_score(int score1, int score2)
{
    score[0] = score1;
    score[1] = score2;
    printf("Score: %d %d\n", score[0], score[1]);
}

void update_player(int player_number)
{
    player = player_number - 1; // player_number is 1 or 2, but player is 0 or 1 (array index)
}

void update_winner(int winner_number)
{
    winner = winner_number;
}

void close_game()
{
}

void pong_init()
{
    quit = 0;
    if (init() == SYSERR)
    {
        return;
    }
    SDL_GetWindowSize(window, &width, &height);

    int state = 0;
    int r = 0;
    Uint32 next_game_tick = SDL_GetTicks();
    while (quit == 0)
    {

        // check for new events every frame
        SDL_PumpEvents();

        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        if (winner != 0)
        {
            if (winner == player)
            {
               printf("YOU WON! 😎\n");
            }
            else
            {
                printf("YOU LOST 😔\n");
            }

            winner = 0;
            quit = 1;
            in_game = FALSE;
        }

        if (keystate[SDL_SCANCODE_ESCAPE])
        {
            close_game();
        }

        if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])
        {
            move_paddle(&paddle[player], height, 1); // 1 is up
            send_paddle_position(paddle[player].x, paddle[player].y, player + 1);
        }
        if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S])
        {
            move_paddle(&paddle[player], height, 0); // 0 is down
            send_paddle_position(paddle[player].x, paddle[player].y, player + 1);
        }

        move_ball(&ball, height, width, paddle[player], player);

        // draw background
        SDL_RenderClear(renderer);
        SDL_FillRect(screen, NULL, 0x000000ff);

        // draw the net
        draw_net(screen);

        // draw the ball
        draw_ball(screen, &ball);

        // draw the paddles
        draw_paddle(screen, paddle);

        // draw the score
        draw_player_score(screen, numbermap, score[0], 1);
        draw_player_score(screen, numbermap, score[1], 2);

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
}

int init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return SYSERR;
    }

    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return SYSERR;
    }

    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return SYSERR;
    }

    // Obtén las dimensiones de la ventana después de crearla
    SDL_GetWindowSize(window, &width, &height);

    // create the screen sruface where all the elemnts will be drawn onto (ball, paddles, net etc)
    screen = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);

    if (screen == NULL)
    {

        printf("Could not create the screen surfce! SDL_Error: %s\n", SDL_GetError());

        return SYSERR;
    }

    // create the screen texture to render the screen surface to the actual display
    screen_texture = SDL_CreateTextureFromSurface(renderer, screen);

    if (screen_texture == NULL)
    {

        printf("Could not create the screen_texture! SDL_Error: %s\n", SDL_GetError());

        return SYSERR;
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

        return SYSERR;
    }

    // Load the gameover image
    end = SDL_LoadBMP("gameover.bmp");

    if (end == NULL)
    {

        printf("Could not Load title image! SDL_Error: %s\n", SDL_GetError());

        return SYSERR;
    }

    // Set the title colourkey.
    Uint32 colorkey = SDL_MapRGB(title->format, 255, 0, 255);
    SDL_SetColorKey(title, SDL_TRUE, colorkey);
    SDL_SetColorKey(numbermap, SDL_TRUE, colorkey);

    return OK;
}