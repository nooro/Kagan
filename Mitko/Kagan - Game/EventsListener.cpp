#include "Game.h"
#include "ServerConnection.h"

void Game::CheckForEvents()
{
    if(SDL_PollEvent(&event))
    {
        //If the window's quit button is pressed exit the game
        if (event.type == SDL_QUIT)
            gameIsRunning = false;

        if(event.key.type == SDL_KEYDOWN)
        {

            //If the escape button is pressed exit the game
            if (event.key.keysym.sym == SDLK_ESCAPE)
                gameIsRunning = false;

            if (event.key.keysym.sym == SDLK_UP)
            {
                Entity::getEntity("Player")->moveTo(0, -0.01);
            }

            if (event.key.keysym.sym == SDLK_DOWN)
            {
                Entity::getEntity("Player")->moveTo(0, 0.01);
            }

            if (event.key.keysym.sym == SDLK_LEFT)
            {
                Entity::getEntity("Player")->moveTo(-0.01, 0);
            }

            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                Entity::getEntity("Player")->moveTo(0.01, 0);
            }

            if (event.key.keysym.sym == SDLK_SPACE)
            {
                character.takeDmg(1);
                health_bar.setCurrency(character.getHp());
            }

            if (event.key.keysym.sym == SDLK_r)
            {
                character.respawn();
                health_bar.setCurrency(character.getHp());
            }
        }


    }
}
