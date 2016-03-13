#include "Game.h"

Game::Game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "Failed to initialize SDL: "<< SDL_GetError() <<endl;
    }

    if( TTF_Init() < 0 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    //Window initialization
    window = SDL_CreateWindow("Kagan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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

    //Load the resources
    Game::LoadTheResources();
}

void Game::Run(string username)
{
    Game::GameLoop();

    Game::Exit();
}

void Game::LoadTheResources()
{
    background.InitBackground("./resources/textures/back.jpg", renderer);
    character.createEntity("Player", 0.5, 0.5, 50, 50, WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT, renderer, "./resources/textures/red.bmp");
    health_bar.init("./resources/textures/healthbar.png", renderer, WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT, 0.05, 0.05, 0.75);
    dmgtxt.init("sans.ttf", 24, White, WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT);
    dmgtxt.setAscend(0.01);
    dmgtxt.setFade(7);
}

void Game::Exit()
{
    delete(&character);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
}
