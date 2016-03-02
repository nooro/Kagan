#include "Map.h"
#include "Game.h"

Map::Map()
{
    hoverTile = NULL;
    Tileset_Image = NULL;
    building = false;
    selectedTileX = 0;
    selectedTileY = 0;
    page = 0;
}

Map::~Map()
{
    //dtor
}

bool Map::LoadTileSet(int layer)
{
    int firstPar;
    int secondPar;
    char spliter;

    //Checks if the image is loaded correctly
    if(Tileset_Image == NULL)
    {
        cout<<"Tile set Image not loaded!"<<endl;
        return false;
    }

    //Checks if the map file is loaded correctly
    if(loadMap == NULL)
    {
        cout<<"Map not loaded!"<<endl;
        return false;
    }

    //Load the map array from a file
    for(int y = 0; y < MAP_Y; y ++)
    {
        for(int x = 0; x < MAP_X; x ++)
        {
            loadMap >> firstPar;
            loadMap >> spliter;
            loadMap >> secondPar;

            //Creates a tile from the given arguments
            tile_map[y][x].LoadTile(x, y, firstPar, secondPar);
        }
    }

    SetLayer(layer);

    return true;
}

void Map::SetLayer(int layer)
{
    for(int y = 0; y < MAP_Y; y ++)
    {
        for(int x = 0; x < MAP_X; x ++)
        {
            tile_map[y][x].yCoord -= layer * TILE_HEIGHT / 2;
        }
    }
}

bool Map::SaveMap()
{
    saveMap.open("./Resources/Maps/temp.map");

     for(int y = 0; y < MAP_Y; y ++)
    {
        for(int x = 0; x < MAP_X; x ++)
        {
            saveMap << tile_map[y][x].tileProperty;
            saveMap << ":";
            saveMap << tile_map[y][x].tileSetCoordX / TILE_WIDTH + tile_map[y][x].tileSetCoordY / TILE_HEIGHT * tile_map[y][x].tileSetY;
            saveMap << " ";

        }

        saveMap << "\n";
    }

    saveMap.close();
}

void Map::RenderMap(SDL_Renderer* Rend, Camera* cam)
{
    for(int i = 0; i < MAP_X; i ++)
    {
        for(int j = 0; j < MAP_Y; j ++)
        {
            if(tile_map[i][j].tileProperty == 0) continue; // Don't Render if the tile is disabled

            tile_map[i][j].DrawTile(Rend, cam, Tileset_Image); // Draw the current tile
        }
    }

    //OnHover(Rend, cam);
}

TILE* Map::GetHoverTile(Camera* cam)
{
    int Mx = 0;
    int My = 0;

    //Gets the mouse X && Y
    SDL_GetMouseState(&Mx, &My);

    Mx -= cam->camX;
    My -= cam->camY;



    //Find the tile coordinates
    for(int i = 0; i < MAP_X; i++)
    {
        for (int j = 0; j < MAP_Y; j++)
        {
            if(tile_map[j][i].hoverTile(Mx, My, cam))
                return &tile_map[j][i];
        }
    }

   return NULL;
}

bool Map::OnHover(SDL_Renderer* Rend, Camera* cam)
{
    //If the building menu is up don't get a new hover tile
    if(building == true)
    {
        return false;
    }

    //Gets a pointer to the hovered tile ... if no tile is hovered it returns false
    if((hoverTile = GetHoverTile(cam)) == NULL)
    {
        cout<<"Mouse out of the map"<<endl;
        return false;
    }

    //Check the pointed tile properties ... if its disabled it return false
    if(hoverTile->tileProperty == 0)
    {
        cout<<"Tile is disabled"<<endl;
        return false;
    }

    cout<<"x: "<<hoverTile->xCoord<<endl;
    cout<<"y: "<<hoverTile->yCoord<<endl;
    cout<<"x1: "<<hoverTile->xCoord + TILE_WIDTH<<endl;
    cout<<"y1: "<<hoverTile->yCoord + TILE_HEIGHT<<endl;

    //Changes the hovered tile to a hovered image
    Game::Draw(Rend, cam, Hover_Image, hoverTile->xCoord * cam->camZoom, hoverTile->yCoord * cam->camZoom, TILE_WIDTH, TILE_HEIGHT, hoverTile->angle, SDL_FLIP_NONE);

    return true;
}
