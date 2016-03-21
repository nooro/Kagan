#include "Game.h"

bool Game::OnInit()
{
    //Initialize everything in SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    //Creating Window             title ,Xpos,Ypos,Width,Height, settings
    if((Window = SDL_CreateWindow("Blank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MIN_WINDOW_X, MIN_WINDOW_Y,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED)) == NULL)
    {
        return false;
    }

    SDL_SetWindowMaximumSize(Window, MAX_WINDOW_X, MAX_WINDOW_Y);
    SDL_SetWindowMinimumSize(Window, MIN_WINDOW_X, MIN_WINDOW_Y);

    SDL_GetWindowSize(Window, &WindowWidth, &WindowHeight);

    Fullscreen = false;

    if((Icon = IMG_Load("./Resources/Images/favicon.png")) == NULL)
    {
        cout<<"Icon not loaded"<<endl;
        return false;
    }

    SDL_SetWindowIcon(Window, Icon);

    // Creating Renderer
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //Check Renderer
    if(Renderer == NULL)
    {
        cout << SDL_GetError() << endl;
        return false;
    }

    //Creating Entities

    if( (Cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND)) == NULL)
    {
        return false;
    }

    if( (DragCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL)) == NULL)
    {
        return false;
    }

    //Load Images

    if(LoadContent() == false)
    {
        cout<<"Load content failed"<<endl;
        return false;
    }

    Character.CreateEntity(0, 0, 75, 75);

    return true;
}

SDL_Texture* Game::OnLoad(SDL_Renderer* Rend, char* File)
{
    SDL_Surface* Surf_Temp = NULL;
    SDL_Texture* Text_Return = NULL;

    if((Surf_Temp = IMG_Load(File)) == NULL)
    {
        cout<<"Surface not loaded"<<endl;
        return NULL;
    }

    if((Text_Return = SDL_CreateTextureFromSurface(Rend, Surf_Temp)) == NULL)
    {
        cout<<"Creating texture from surface failed! Check your Renderer."<<endl;
        return NULL;
    }

    SDL_FreeSurface(Surf_Temp);

    return Text_Return;
}
