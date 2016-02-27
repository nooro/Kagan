#include "Game.h"

bool Game::LoadContent()
{
    ///TEXTURES

    empty_layer.Tileset_Image = OnLoad(Renderer, "./Resources/Images/iso64x64.png");

    empty_layer.Hover_Image = OnLoad(Renderer, "./Resources/Images/HoverImage.png");

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

    empty_layer.loadMap.open("./Resources/Maps/empty_layer.map");

    if(empty_layer.LoadTileSet() == false)
    {
        cout<<"Map not loaded"<<endl;
        Sleep(1000);
        return false;
    }


    return true;
}
