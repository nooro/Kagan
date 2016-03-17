#include "Game.h"

void Game::Render()
{
    SDL_RenderClear(renderer);


    background.render(renderer);
    character.render(renderer);
    health_bar.render(renderer);
    list<dmgFloat>::iterator it = dmg_text.begin();
    while(it != dmg_text.end() && dmg_text.size() > 0)
    {
        if(!it->exist)
            dmg_text.erase(it++);
        else
        {
            it->render(renderer);
            ++it;
        }
    }


    SDL_RenderPresent(renderer);
}
