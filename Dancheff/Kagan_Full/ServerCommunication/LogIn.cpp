#include "LogIn.h"

LogIn::LogIn()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        cout << "Failed to initialize SDL: " << SDL_GetError() << endl;

    window = SDL_CreateWindow("Log In",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 360,
                              SDL_WINDOW_SHOWN );
    if(window == NULL)
        cout << "Failed to create window: " << SDL_GetError() << endl;


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
        cout << "Failed to create renderer: " << SDL_GetError() << endl;
}

LogIn::~LogIn()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
