#include "Game.h"

void Game::Render()
{
    SDL_RenderClear(renderer);

    test.render(renderer, 0.0, 0.0);

    SDL_RenderPresent(renderer);
}
