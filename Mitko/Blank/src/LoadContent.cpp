#include "Game.h"

bool Game::LoadContent()
{
    ///TEXTURES

    Map1.Tileset_Image = OnLoad(Renderer, "./Resources/Images/iso64x64.png");

    Map1.Hover_Image = OnLoad(Renderer, "./Resources/Images/HoverImage.png");

    Map2.Tileset_Image = OnLoad(Renderer, "./Resources/Images/iso64x64.png");

    Map2.Hover_Image = OnLoad(Renderer, "./Resources/Images/HoverImage.png");

    Map3.Tileset_Image = OnLoad(Renderer, "./Resources/Images/iso64x64.png");

    Map3.Hover_Image = OnLoad(Renderer, "./Resources/Images/HoverImage.png");

    Character.Image = OnLoad(Renderer, "./Resources/Images/SIdle1.png");

    if(!Idle[0].Load(Renderer, "./Resources/Images/SIdle1.png", 50, 500, 400)) return false;
    if(!Idle[1].Load(Renderer, "./Resources/Images/SIdle2.png", 50, 500, 400)) return false;
    if(!Idle[2].Load(Renderer, "./Resources/Images/SIdle3.png", 50, 500, 400)) return false;
    if(!Idle[3].Load(Renderer, "./Resources/Images/SIdle4.png", 50, 500, 400)) return false;
    if(!Idle[4].Load(Renderer, "./Resources/Images/SIdle5.png", 50, 500, 400)) return false;
    if(!Idle[5].Load(Renderer, "./Resources/Images/SIdle6.png", 50, 500, 400)) return false;
    if(!Idle[6].Load(Renderer, "./Resources/Images/SIdle7.png", 50, 500, 400)) return false;
    if(!Idle[7].Load(Renderer, "./Resources/Images/SIdle8.png", 50, 500, 400)) return false;

    if(Map1.Hover_Image == NULL)
    {
        return false;
    }

    if(Map1.Tileset_Image == NULL)
    {
        return false;
    }

    if(Map2.Hover_Image == NULL)
    {
        return false;
    }

    if(Map2.Tileset_Image == NULL)
    {
        return false;
    }

    if(Map3.Hover_Image == NULL)
    {
        return false;
    }

    if(Map3.Tileset_Image == NULL)
    {
        return false;
    }



    if(Character.Image == NULL)
    {
        return false;
    }

    SDL_SetTextureAlphaMod(Map1.Hover_Image, 100);

    ///MAPS

    Map1.loadMap.open("./Resources/Maps/layer1.map");

    if(Map1.LoadTileSet(0) == false)
    {
        cout<<"Map not loaded"<<endl;
        Sleep(1000);
        return false;
    }

    Map2.loadMap.open("./Resources/Maps/layer2.map");

    if(Map2.LoadTileSet(1) == false)
    {
        cout<<"Map not loaded"<<endl;
        Sleep(1000);
        return false;
    }

    Map3.loadMap.open("./Resources/Maps/layer3.map");

    if(Map3.LoadTileSet(2) == false)
    {
        cout<<"Map not loaded"<<endl;
        Sleep(1000);
        return false;
    }

    return true;
}
