#include "TILE.h"
#include "Game.h"

TILE::TILE()
{
    tileSetY = 10;
}

TILE::~TILE()
{
    //dtor
}

void TILE::LoadTile(int x, int y, int prop, int xImg)//, int layer)
{
    xCoord = x * (TILE_WIDTH / 2);
    yCoord = y * (TILE_HEIGHT / 2);

    //xCoord -= layer * TILE_WIDTH;
    //yCoord -= layer * TILE_HEIGHT;

    angle = 0;

    MakeIso();

    tileProperty = prop;

    tileSetCoordY = xImg / tileSetY;
    tileSetCoordX = (xImg - tileSetCoordY * tileSetY);

    tileSetCoordY *= TILE_HEIGHT;
    tileSetCoordX *= TILE_WIDTH;
}

void TILE::DrawTile(SDL_Renderer* Rend, Camera* cam, SDL_Texture* TileTemp)
{
    Game::Draw(Rend, cam, TileTemp, xCoord * cam->camZoom, yCoord * cam->camZoom, TILE_WIDTH, TILE_HEIGHT, tileSetCoordX, tileSetCoordY, TILE_WIDTH, TILE_HEIGHT, angle, SDL_FLIP_NONE);
}

void TILE::MakeIso()
{
    int x = xCoord;
    int y = yCoord;

    xCoord = x - y;
    yCoord = (x + y) / 2;
}

bool TILE::hoverTile(int Mx, int My, Camera* cam)
{
    if(Mx < xCoord * cam->camZoom) return false;
    else if(Mx > (xCoord + TILE_WIDTH) * cam->camZoom) return false;
    else if(My < yCoord * cam->camZoom) return false;
    else if(My > (yCoord + TILE_HEIGHT / 2) * cam->camZoom ) return false;

    return true;
}



