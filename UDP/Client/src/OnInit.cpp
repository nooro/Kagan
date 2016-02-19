#include "Client.h"

bool Client::OnInit()
{
    if ( SDLNet_Init() == -1 )
    {
        cout << "\nSDLNet_Init failed : " << SDLNet_GetError() << endl;
        return false;
    }

    if ( SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        cout<< "\nSDL_Init failed : " << SDL_GetError() <<endl;
        return false;
    }

    if((Window = SDL_CreateWindow("Client", 300, 300, 640, 480, SDL_WINDOW_SHOWN)) == NULL)
    {
        cout<< "\nSDL_CreateWindow failed : " << SDL_GetError() <<endl;
        return false;
    }

    if((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        cout <<"\nSDL_CreateRenderer failed : "<< SDL_GetError() << endl;
        return false;
    }

    if(LoadContent() == false)
    {
        cout<< "\nLoadContent failed" <<endl;
        return false;
    }

    return true;
}

SDL_Texture* Client::OnLoad(SDL_Renderer* Rend, char* File)
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
