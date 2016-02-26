#include "Game.h"

Game::Game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "Failed to initialize SDL: "<< SDL_GetError() <<endl;
    }

    //Window initialization
    window = SDL_CreateWindow("Kagan", 0, 0,
                              640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(window == NULL)
    {
        cout << "Window initialization error: " << SDL_GetError() << endl;
    }

    //Renderer initialization

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
    {
        cout << "Renderer initialization error: " << SDL_GetError() << endl;
    }

    //Returns the window resolution
    SDL_GetWindowSize(window, &WINDOW_MAX_WIDTH, &WINDOW_MAX_HEIGHT);

    //Re-Init the textures with the new resolution
    test = LGTexture(WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT);

    //Load the resources
    Game::LoadTheResources();
}

void Game::Run(string username)
{
    Game::GameLoop();
}

void Game::LoadTheResources()
{
    test.load(renderer, "./resources/textures/red.bmp");
}
