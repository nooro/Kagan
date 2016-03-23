#include "LogIn.h"

LogIn::LogIn()
{

    ServerCommunication server(serverIP);

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        cout << "Failed to initialize SDL: " << SDL_GetError() << endl;

    if(TTF_Init() < 0)
        cout << "Failed to initialize SDL_TTF: " << SDL_GetError() << endl;


    //Create the window
    window = SDL_CreateWindow("Log In",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              GetScreenWidth() / 2, GetScreenHeight() / 2,
                              SDL_WINDOW_SHOWN);

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

    //Initialize the input field for the user-name
    usernameInputField = new InputField(renderer);

    //Initialize the input field for the password
    passwordInputField = new InputField(renderer);

    //Initialize the log-in button
    InitTheButton();

    //Initialize the input fields
    InitTheInputFields();

    //Add the user-name label texture to the renderer
    SDL_RenderCopy(renderer, usernameLabel, NULL, &usernameLabelRect);

    //Add the user-name label texture to the renderer
    SDL_RenderCopy(renderer, passwordLabel, NULL, &passwordLabelRect);

    //Render all the interface
    SDL_RenderPresent(renderer);

    logInWindowIsActive = true;
    Loop();


    if(server.Connection())
    {
        cout << "Log-in status: " << server.LogIn(usernameInputField->GetInputText(), passwordInputField->GetInputText());
    }
    else
    {
        cout << "Can not connect to the server!" << endl;
    }
}

LogIn::~LogIn()
{
    delete(&logInButton);
    delete(&usernameInputField);
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
            if (event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT)
                logInWindowIsActive = false;

            //Check for events with the log-in button
            if(logInButton.isHover())
                logInButton.RenderHover(renderer);
            else
                logInButton.Render(renderer);

            if(logInButton.isClicked(&event))
                logInWindowIsActive = false;

            //Check for events with the user-name input field
            if(usernameInputField->isHover())
                usernameInputField->RenderHover();
            else
                usernameInputField->Render();

            if(usernameInputField->isClicked(&event))
            {
                usernameInputField->isActive = true;
                passwordInputField->isActive = false;
            }
            if(usernameInputField->isActive)
                usernameInputField->Input(&event);

            //Check for events with the password input field
            if(passwordInputField->isHover())
                passwordInputField->RenderHover();
            else
                passwordInputField->Render();

            if(passwordInputField->isClicked(&event))
            {
                usernameInputField->isActive = false;
                passwordInputField->isActive = true;
            }
            if(passwordInputField->isActive)
                passwordInputField->Input(&event);

            SDL_RenderPresent(renderer);
        }
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

void LogIn::InitTheInputFields()
{
///USERNAME INPUT FIELD
    //Initialize the rectangle for the user-name label
    usernameLabelRect = { GetScreenWidth() / 10, GetScreenHeight() / 6, 150, 50};

    //Coordinates
    usernameInputField->SetX(GetScreenWidth() / 4.5);
    usernameInputField->SetY(GetScreenHeight() / 5.5);

    //Dimensions
    usernameInputField->SetHeight(GetScreenHeight() / 18);
    usernameInputField->SetWidth(GetScreenWidth() / 5);

    //Texture
    usernameInputField->SetTexture(inputFieldTexture);
    usernameInputField->SetHoverTexture(inputFieldTextureHover);

    //Add the user-name input field to the renderer to be ready for presenting to the screen
    usernameInputField->Render();

    //Set limitation for the input length
    usernameInputField->SetCharLimit(10);

    //Make it active so text can be written
    usernameInputField->isActive = true;

///PASSWORD INPUT FIELD
    //Initialize the rectangle for the user-name label
    passwordLabelRect = { GetScreenWidth() / 10, GetScreenHeight() / 3.6, 150, 50};

    //Set the input type to password to show '*' for the characters
    passwordInputField->type = "password";

    //Coordinates
    passwordInputField->SetX(GetScreenWidth() / 4.5);
    passwordInputField->SetY(GetScreenHeight() / 3.5);

    //Dimensions
    passwordInputField->SetHeight(GetScreenHeight() / 18);
    passwordInputField->SetWidth(GetScreenWidth() / 5);

    //Texture
    passwordInputField->SetTexture(inputFieldTexture);
    passwordInputField->SetHoverTexture(inputFieldTextureHover);

    //Add the user-name input field to the renderer to be ready for presenting to the screen
    passwordInputField->Render();

    //Set limitation for the input length
    passwordInputField->SetCharLimit(10);
}

void LogIn::InitTheTextures()
{
    //Initialize font used for the labels
    labelFont = TTF_OpenFont("Resources/Fonts/Chiller.ttf", 999);

    //Initialize the color for the labels
    labelColor = {255, 255, 255, 0};

    //Create the logo
    logoTexture = CreateTexture("Resources/Textures/log-in/Logo.png", renderer);
    if(logoTexture == NULL)
        cout << "Failed to create logo texture: " << IMG_GetError() << endl;
    //Initialize the rectangle for the logo texture
    logoRect = { 0, 0, GetScreenWidth() / 8.55, GetScreenHeight() / 7.2 };

    //Create the background texture
    backgroundTexture = CreateTexture("Resources/Textures/log-in/bg.jpg", renderer);
    if(backgroundTexture == NULL)
        cout << "Failed to create background texture: " << IMG_GetError() << endl;

    //Create the window border texture
    windowBorder = CreateTexture("Resources/Textures/log-in/windowBorder.png", renderer);
    if(windowBorder == NULL)
        cout << "Failed to create window border texture: " << IMG_GetError() << endl;

    //Create the button texture
    buttonTexture = CreateTexture("Resources/Textures/log-in/logInButton.png", renderer);
    if(buttonTexture == NULL)
        cout << "Failed to create button texture: " << IMG_GetError() << endl;

    //Create the button-hover texture
    buttonHoverTexture = CreateTexture("Resources/Textures/log-in/hoverLogInButton.png", renderer);
    if(buttonHoverTexture == NULL)
        cout << "Failed to create button-hover texture: " << IMG_GetError() << endl;

    //Create the user-name label texture
    usernameLabel = CreateTextTexture(renderer, "Username:", labelFont, usernameLabelRect.h, labelColor);
    if(buttonHoverTexture == NULL)
        cout << "Failed to create username label texture: " << IMG_GetError() << endl;

    //Create the password label texture
    passwordLabel = CreateTextTexture(renderer, "Password:", labelFont, passwordLabelRect.h, labelColor);
    if(buttonHoverTexture == NULL)
        cout << "Failed to create password label texture: " << IMG_GetError() << endl;

    //Initialize input fields border texture
    inputFieldTexture = CreateTexture("Resources/Textures/log-in/input_field.png", renderer);
    if(inputFieldTexture == NULL)
        cout << "Failed to create input field border texture: " << IMG_GetError() << endl;

    //Initialize input fields hover border texture
    inputFieldTextureHover = CreateTexture("Resources/Textures/log-in/input_field_hover.png", renderer);
    if(inputFieldTextureHover == NULL)
        cout << "Failed to create input field hover border texture: " << IMG_GetError() << endl;
}
