#include "Game.h"

void Game::CheckForEvents()
{
    if(SDL_PollEvent(&event))
    {
        //Quit button = Escape the program
        if (event.type == SDL_QUIT)
            gameIsRunning = false;

        //Escape button = Escape the program
        if (event.key.keysym.sym == SDLK_ESCAPE)
            gameIsRunning = false;

    }
}
