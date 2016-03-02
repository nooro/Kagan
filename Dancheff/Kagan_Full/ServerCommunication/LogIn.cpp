#include "LogIn.h"

LogIn::LogIn()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        cout << "Failed to initialize SDL: " << SDL_GetError() << endl;

    window = SDL_CreateWindow("Log In",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              GetScreenWidth() / 2, GetScreenHeight() / 2,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if(window == NULL)
        cout << "Failed to create window: " << SDL_GetError() << endl;


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
        cout << "Failed to create renderer: " << SDL_GetError() << endl;

    backgroundTexture = CreateTexture("castle.jpg", renderer);
    if(backgroundTexture == NULL)
        cout << "Failed to create background texture: " << IMG_GetError() << endl;

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    SDL_RenderPresent(renderer);

    logInWindowIsActive = true;
    Loop();
}

LogIn::~LogIn()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void LogIn::Loop()
{
    while(logInWindowIsActive)
    {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            logInWindowIsActive = false;

        if(logInButton.isClicked())
            cout << "The button was clicked" << endl;
    }
}
