#include "Game.h"

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
}
