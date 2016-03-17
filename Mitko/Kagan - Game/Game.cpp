#include "Game.h"

Game::Game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) // Initialize everything we need for SDL
    {
        cout << "Failed to initialize SDL: "<< SDL_GetError() <<endl; // if there is an error catch it and prints on the console
    }

    if( TTF_Init() < 0 ) // Initialize SDL_TTF for the text
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() ); // if there is an error catch it and prints on the console
    }

    //Window initialization
    window = SDL_CreateWindow("Kagan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(window == NULL)
    {
        cout << "Window initialization error: " << SDL_GetError() << endl; // if there is an error catch it and prints on the console
    }

    //Renderer initialization
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
    {
        cout << "Renderer initialization error: " << SDL_GetError() << endl; // if there is an error catch it and prints on the console
    }

    //Returns the window resolution
    SDL_GetWindowSize(window, &WINDOW_MAX_WIDTH, &WINDOW_MAX_HEIGHT);

    //Load the resources
    Game::LoadTheResources();
}

void Game::Run(string username)
{
    //Run the main game loop
    Game::GameLoop();
    //When the main game loop end exit the game
    Game::Exit();
}

void Game::LoadTheResources()
{
    //Load the background texture
    background.InitBackground("./resources/textures/back.jpg", renderer);
    //Create an entity for the character and load its textures
    character.createEntity("Player", 0.5, 0.5, 50, 50, WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT, renderer, "./resources/textures/red.bmp");
    //Initialize the health bar and load its textures
    health_bar.init("./resources/textures/healthbar.png", renderer, WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT, 0.05, 0.05, 0.75);
    //Initialize the floating text and load its font
    dmgtxt.init("sans.ttf", 24, White, WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT);
    dmgtxt.setAscend(0.01); // Sets the speed the text ascend
    dmgtxt.setFade(7); // Set the text fade speed
}

void Game::Exit()
{
    //delete the entity for the character
    delete(&character);

    //Free the memory for the window
    SDL_DestroyWindow(window);
    //Free the memory for the renderer
    SDL_DestroyRenderer(renderer);

    //Quit SDL
    SDL_Quit();
}
