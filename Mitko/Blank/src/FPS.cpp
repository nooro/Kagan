#include "Game.h"

int i = 0;
Uint32 sec;
int fps = 0;

void Game::OnStartup()
{
    start = SDL_GetTicks();
}

void Game::FrameRate(int FPS)
{
    if(1000/FPS > SDL_GetTicks() - start)
    {
        SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
    }


    i++;
    if(1000 < SDL_GetTicks() - sec)
    {
        sec = SDL_GetTicks();
        fps = i;
        i = 0;
    }
    cout << fps <<endl;
}
