#include "Game.h"

bool Game::LoadContent()
{
    ///TEXTURES

    handSurf = IMG_Load("./Resources/Images/cursor.png");
    if(handSurf == NULL)
        return false;

    hand = SDL_CreateColorCursor(handSurf, 0, 0);

    if(hand == NULL)
        return false;

    SDL_SetCursor(hand);


    empty_layer.Tileset_Image = OnLoad(Renderer, TILESET);

    empty_layer.Hover_Image = OnLoad(Renderer, TILESET);

    Character.Image = OnLoad(Renderer, "./Resources/Images/ogre.png");

    if(empty_layer.Hover_Image == NULL)
    {
        return false;
    }

    if(empty_layer.Tileset_Image == NULL)
    {
        return false;
    }

    if(Character.Image == NULL)
    {
        return false;
    }

    SDL_SetTextureAlphaMod(empty_layer.Hover_Image, 100);

    ///MAPS

    empty_layer.loadMap.open("./Resources/empty_layer.layer");

    if(empty_layer.LoadTileSet() == false)
    {
        cout<<"Map not loaded"<<endl;
        Sleep(1000);
        return false;
    }


    return true;
}
