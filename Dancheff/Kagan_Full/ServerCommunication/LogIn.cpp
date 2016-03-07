#include "LogIn.h"

LogIn::LogIn()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        cout << "Failed to initialize SDL: " << SDL_GetError() << endl;

    if(TTF_Init() < 0)
        cout << "Failed to initialize SDL_TTF: " << SDL_GetError() << endl;

    //Create the window
    window = SDL_CreateWindow("Log In",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              GetScreenWidth() / 2, GetScreenHeight() / 2,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS );

    if(window == NULL)
        cout << "Failed to create window: " << SDL_GetError() << endl;


    //Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
        cout << "Failed to create renderer: " << SDL_GetError() << endl;

    //Initialize the textures
    InitTheTextures();

    //Add the background texture to the renderer
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    //Add the window border texture to the renderer
    SDL_RenderCopy(renderer, windowBorder, NULL, NULL);

    //Add the logo texture to the renderer
    SDL_RenderCopy(renderer, logoTexture, NULL, &logoRect);

    //Initialize the log-in button
    InitTheButton();

    //Render all the interface
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
        if(SDL_PollEvent(&event))
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                logInWindowIsActive = false;

            if(logInButton.isHover())
            {
                logInButton.RenderHover(renderer);
            }
            else logInButton.Render(renderer);
        }
        SDL_RenderPresent(renderer);
    }
}



void LogIn::InitTheButton()
{
    //Dimensions
    logInButton.SetHeight(GetScreenHeight() / 12);
    logInButton.SetWidth(GetScreenWidth() / 9);

    //Coordinates
    logInButton.SetX(GetScreenWidth() / 4 - logInButton.GetWidth() / 2);
    logInButton.SetY(GetScreenHeight() / 2.5);

    //Texture
    logInButton.SetTexture(buttonTexture);
    logInButton.SetHoverTexture(buttonHoverTexture);

    //Add the button to the renderer to be ready for presenting to the screen
    logInButton.Render(renderer);
}

void LogIn::InitTheTextures()
{
    //Create the logo
    logoTexture = CreateTexture("Resources/Textures/log-in/Logo.png", renderer);
    if(logoTexture == NULL)
        cout << "Failed to create background texture: " << IMG_GetError() << endl;
    //Initialize the rectangle for the logo texture
    logoRect = { 0, 0, GetScreenWidth() / 8.55, GetScreenHeight() / 7.2 };

    //Create the background texture
    backgroundTexture = CreateTexture("Resources/Textures/log-in/bg.jpg", renderer);
    if(backgroundTexture == NULL)
        cout << "Failed to create background texture: " << IMG_GetError() << endl;

    //Create the window border texture
    windowBorder = CreateTexture("Resources/Textures/log-in/windowBorder.png", renderer);
    if(windowBorder == NULL)
        cout << "Failed to create background texture: " << IMG_GetError() << endl;
    //Create the button texture
    buttonTexture = CreateTexture("Resources/Textures/log-in/logInButton.png", renderer);
    if(buttonTexture == NULL)
        cout << "Failed to create button texture: " << IMG_GetError() << endl;

    //Create the button-hover texture
    buttonHoverTexture = CreateTexture("Resources/Textures/log-in/hoverLogInButton.png", renderer);
    if(buttonHoverTexture == NULL)
        cout << "Failed to create button-hover texture: " << IMG_GetError() << endl;
}
