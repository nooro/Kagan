#include "Game.h"

void Game::GameLoop()
{
    while(gameIsRunning)
    {
        Game::CheckForEvents();

        Game::Render();

        SDL_Delay(1000/60);
    }
}
