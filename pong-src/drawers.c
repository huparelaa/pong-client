#include <SDL.h>
#include "drawers.h"

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