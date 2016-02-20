#include "Game.h"

Game::Game()
{
//Window initialization
    window = SDL_CreateWindow("Kagan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOW_FULLSCREEN_DESKTOP, SDL_WINDOW_FULLSCREEN_DESKTOP, SDL_WINDOW_SHOWN);
    if(window == NULL)
        cout << "Window initialization error: " << SDL_GetError() << endl;

//Renderer initialization
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
        cout << "Renderer initialization error: " << SDL_GetError() << endl;

//Load the resources
    Game::LoadTheResources();
}

void Game::Run(string username)
{
    Game::GameLoop();
}

void Game::LoadTheResources()
{

}
