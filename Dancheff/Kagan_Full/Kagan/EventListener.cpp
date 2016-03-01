#include "Game.h"

void Game::CheckForEvents()
{
    if(SDL_PollEvent(&event))
    {
        //If the window's quit button is pressed exit the game
        if (event.type == SDL_QUIT)
            gameIsRunning = false;

        //If the escape button is pressed exit the game
        if (event.key.keysym.sym == SDLK_ESCAPE)
            gameIsRunning = false;

    }
}
