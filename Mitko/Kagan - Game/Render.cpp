#include "Game.h"

void Game::Render()
{
    SDL_RenderClear(renderer);


    background.render(renderer);
    character.render(renderer);
    health_bar.render(renderer);


    SDL_RenderPresent(renderer);
}
