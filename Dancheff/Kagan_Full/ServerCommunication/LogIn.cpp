#include "LogIn.h"

SDL_Texture *CreateTexture(std::string filePath, SDL_Renderer* textureRenderer){
    SDL_Texture* texture = NULL;
    SDL_Surface* temp_surface = IMG_Load(filePath.c_str());

    texture = SDL_CreateTextureFromSurface(textureRenderer, temp_surface);
    SDL_FreeSurface(temp_surface);
    return texture;
}

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
        CheckForEvents();
    }
}

void LogIn::CheckForEvents()
{
    if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                logInWindowIsActive = false;
        }
}
