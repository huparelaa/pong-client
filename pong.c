#include "pong.h"
#include "globals.h"
#include <SDL.h> //SDL version 2.0
#include "pong-src/drawers.h"

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

void pong_init()
{
    if (init() == SYSERR)
    {
        return;
    }
    SDL_GetWindowSize(window, &width, &height);

    int sleep = 0;
    int quit = 0;
    int state = 0;
    int r = 0;
    Uint32 next_game_tick = SDL_GetTicks();
    while (quit == 0)
    {

        // check for new events every frame
        SDL_PumpEvents();

        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_ESCAPE])
        {
            in_game = FALSE;
            quit = 1;
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
        else if (state == 1)
        {
            draw_net(screen);
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

    if(window == NULL)
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