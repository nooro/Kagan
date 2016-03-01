#include "Game.h"


Game::Game()
{
    //SDL initialization
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        cout << "Failed to initialize SDL: "<< SDL_GetError() << endl;

    //Window initialization
    window = SDL_CreateWindow("Kagan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(window == NULL)
        cout << "Window initialization error: " << SDL_GetError() << endl;

    //Renderer initialization
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
        cout << "Renderer initialization error: " << SDL_GetError() << endl;

    //Get the window resolution
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    //Load the resources
    Game::LoadTheResources();

    gameIsRunning = true;
}

Game::~Game()
{
    //FreeTheTextures();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::Run(string username)
{
    GameLoop();
}
