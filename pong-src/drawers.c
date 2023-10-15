#include <SDL.h>
#include "drawers.h"
#include "ball.h"
void draw_menu(SDL_Surface *screen, SDL_Surface *title)
{
    SDL_Rect src;
    SDL_Rect dest;

    src.x = 0;
    src.y = 0;
    src.w = title->w;
    src.h = title->h;

    dest.x = (screen->w / 2) - (src.w / 2);
    dest.y = (screen->h / 2) - (src.h / 2);
    dest.w = title->w;
    dest.h = title->h;

    SDL_BlitSurface(title, &src, screen, &dest);
}

void draw_net(SDL_Surface *screen)
{
    SDL_Rect net;

    net.x = screen->w / 2;
    net.y = 20;
    net.w = 5;
    net.h = 15;

    // draw the net
    int i, r;

    for (i = 0; i < 15; i++)
    {

        r = SDL_FillRect(screen, &net, 0xffffffff);

        if (r != 0)
        {

            printf("fill rectangle faliled in func draw_net()");
        }

        net.y = net.y + 30;
    }
}

void draw_ball(SDL_Surface *screen, ball_t *ball)
{

    SDL_Rect src;

    src.x = ball->x;
    src.y = ball->y;
    src.w = 10; // ball->w
    src.h = 10; // ball->h

    int r = SDL_FillRect(screen, &src, 0xffffffff);

    if (r != 0)
    {

        printf("fill rectangle faliled in func drawball()");
    }
}

void draw_player_score(SDL_Surface *screen, SDL_Surface *numbermap, int score, int player_number)
{

    SDL_Rect src;
    SDL_Rect dest;

    src.x = 0;
    src.y = 0;
    src.w = 64;
    src.h = 64;
    if (player_number == 1)
    {
        dest.x = (screen->w / 2) - src.w - 12; // 12 is just padding spacing
    }
    else
    {
        dest.x = (screen->w / 2) + 12; // move to the right
    }
    dest.y = 0;
    dest.w = 64;
    dest.h = 64;

    if (score > 0 && score < 10)
    {

        src.x += src.w * score;
    }

    SDL_BlitSurface(numbermap, &src, screen, &dest);
}

void draw_paddle(SDL_Surface *screen, paddle_t paddle[2])
{

    SDL_Rect src;
    int i;

    for (i = 0; i < 2; i++)
    {

        src.x = paddle[i].x;
        src.y = paddle[i].y;
        src.w = 10;  //paddle[i].w;
        src.h = 50; //paddle[i].h;

        int r = SDL_FillRect(screen, &src, 0xffffffff);

        if (r != 0)
        {

            printf("fill rectangle faliled in func draw_paddle()");
        }
    }
}
