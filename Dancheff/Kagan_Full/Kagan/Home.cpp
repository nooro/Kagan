#include "Home.h"

Home::Home()
{
    //Initialize the window
    window = SDL_CreateWindow("Kagan III - Home", 0, 0, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(window == NULL)
        cout << "Failed to initialize the home window: " << SDL_GetError() << endl;

    //Initialize the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
        cout << "Failed to initialize the renderer: " << SDL_GetError() << endl;

    //Initialize the size of the cursor
    cursorRect.w = 35;
    cursorRect.h = 35;
    //Hide the default cursor
    SDL_ShowCursor(false);

    //Initialize the Chiller font
    font_chiller = TTF_OpenFont("Resources/Fonts/Chiller.ttf", 999);

    //Initialize the user-name input label texture
    InitTheUsernameLabel();

    //Initialize the character bar
    InitTheCharacterBar();

    //Initialize all the textures used in the home window
    InitTheTextures();

    //Initialize the play button
    InitThePlayButton();

    //Add the background texture to the renderer
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    //Add the user-name label texture to the renderer
    SDL_RenderCopy(renderer, usernameLabel, NULL, &usernameLabelRect);

    //And GOD said "Let there be light!". (aka show everything to the screen)
    SDL_RenderPresent(renderer);

    homeWindowIsActive = true;
    MainLoop();
}

Home::~Home()
{
    SDL_DestroyTexture(backgroundTexture);
}

void Home::MainLoop()
{
    while(homeWindowIsActive)
    {
        SDL_RenderClear(renderer);

        SDL_GetMouseState(&cursorRect.x, &cursorRect.y);

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        SDL_RenderCopy(renderer, usernameLabel, NULL, &usernameLabelRect);

        AnimateTheCharacter();
        CheckForEvents();

        SDL_RenderCopy(renderer, cursor, NULL, &cursorRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }
}

void Home::InitThePlayButton()
{
    //Dimensions
    playButton.SetHeight(GetScreenHeight() / 10);
    playButton.SetWidth(GetScreenWidth() / 7);

    //Coordinates
    playButton.SetX(GetScreenWidth() / 2 - playButton.GetWidth() / 2);
    playButton.SetY(20);

    //Texture
    playButton.SetTexture(playButtonTexture);
    playButton.SetHoverTexture(playButtonHoverTexture);

    //Add the button to the renderer to be ready for presenting to the screen
    playButton.Render(renderer);
}

void Home::CheckForEvents()
{
    if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            homeWindowIsActive = false;

        if(playButton.isClicked(&event))
        {
            // TODO
        }
    }
    //Check for events with the log-in button
    if(playButton.isHover())
        playButton.RenderHover(renderer);
    else
        playButton.Render(renderer);
}

void Home::InitTheTextures()
{
    //Cursor
    cursor = CreateTexture("Resources/Textures/home-window/c.png", renderer);
    if(cursor == NULL)
        cout << "Failed to create the cursor texture: " << SDL_GetError() << endl;

    //Background texture
    backgroundTexture = CreateTexture("Resources/Textures/home-window/background.jpg", renderer);
    if(backgroundTexture == NULL)
        cout << "Failed to create the home window background texture: " << SDL_GetError() << endl;

    //User-name label texture
    usernameLabel = CreateTextTexture(renderer, usernameLabelText, font_chiller, usernameLabelColor);
    if(usernameLabel == NULL)
        cout << "Failed to create the user-name label texture: " << SDL_GetError() << endl;

    //Character bar background texture
    characterBarBackground = CreateTexture("Resources/Textures/home-window/bg.jpg", renderer);
    if(characterBarBackground == NULL)
        cout << "Failed to create the character bar background texture: " << SDL_GetError() << endl;

    //Character sprite-sheet
    characterTexture = CreateTexture("Resources/Textures/home-window/skeli-animation.png", renderer);
    if(characterTexture == NULL)
        cout << "Failed to create the character sprite-sheet texture: " << SDL_GetError() << endl;

    //Play button
    playButtonTexture = CreateTexture("Resources/Textures/home-window/play-button.png", renderer);
    if(playButtonTexture == NULL)
        cout << "Failed to create the play button texture: " << SDL_GetError() << endl;

    //Play button hover
    playButtonHoverTexture = CreateTexture("Resources/Textures/home-window/play-button-hover.png", renderer);
    if(playButtonHoverTexture == NULL)
        cout << "Failed to create the play button hover texture: " << SDL_GetError() << endl;
}

void Home::InitTheUsernameLabel()
{
    usernameLabelColor = {255, 255, 255, 0}; //White color as rgba
    usernameLabelText = "Welcome " + User::username + "...";

    usernameLabelRect.x = GetScreenWidth() / 16;
    usernameLabelRect.y = GetScreenHeight() / 15;
    usernameLabelRect.w = GetScreenWidth() / usernameLabelText.length() * 3;
    usernameLabelRect.h = GetScreenHeight() / usernameLabelText.length() * 2;
}

void Home::InitTheCharacterBar()
{
    characterBarRect.x = GetScreenWidth() / 20;
    characterBarRect.y = GetScreenHeight() / 5;
    characterBarRect.w = GetScreenWidth() / 3.5;
    characterBarRect.h = GetScreenHeight() / 1.5;

    spriteSheetRect.x = GetScreenWidth() / 20;
    spriteSheetRect.y = GetScreenHeight() / 5;
    spriteSheetRect.w = GetScreenWidth() / 3.5;
    spriteSheetRect.h = GetScreenHeight() / 1.5;

    characterRect.w = 640;
    characterRect.h = 580;
    characterRect.x = 0;
    characterRect.y = 0;
}

void Home::AnimateTheCharacter()
{
    characterRect.x += 640;
    if(characterRect.x >= 6400)
    {
        characterRect.x = 0;
        characterRect.y += 580;
        if(characterRect.y >= 2900)
        {
            characterRect.y = 0;
        }
    }
    SDL_RenderCopy(renderer, characterTexture, &characterRect, &characterBarRect);
}
