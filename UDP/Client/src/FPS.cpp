#include "Client.h"

void Client::OnStartup()
{
    start = SDL_GetTicks();
}

void Client::FrameRate(int FPS)
{
    if(1000/FPS > SDL_GetTicks() - start)
    {
        SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
    }
}
