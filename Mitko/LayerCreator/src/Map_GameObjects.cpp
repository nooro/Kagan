#include "Map.h"
#include "Game.h"

void Map::ChangeTile()
{
    int mX, mY;

    SDL_GetMouseState(&mX, &mY);

    if(mY < 630) return;

    if(mX < 400) return;
    if(mX > 400 + 640) return;

    selectedTileX = (mX - 400) / TILE_WIDTH;
    selectedTileY = page;
}

void Map::DeleteTile()
{
    int mX, mY;

    SDL_GetMouseState(&mX, &mY);

    if(mY > 630) return;

    if(hoverTile == NULL) return;

    hoverTile->tileProperty = 0;
}

void Map::PlaceTile()
{
    int mX, mY;

    SDL_GetMouseState(&mX, &mY);

    if(mY > 630) return;

    if(hoverTile == NULL) return;

    hoverTile->tileSetCoordX = selectedTileX * TILE_WIDTH;
    hoverTile->tileSetCoordY = selectedTileY * TILE_HEIGHT;
}

void Map::DrawTileList(SDL_Renderer* Rend, Camera* cam)
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 620;
    rect.h = 100;
    rect.w = 1367;

    SDL_SetRenderDrawColor(Rend, 255, 255, 255, 255);

    SDL_RenderFillRect(Rend, &rect);

    SDL_SetRenderDrawColor(Rend, 0, 0, 0, 0);

    Game::Draw(Rend, cam, Tileset_Image, 400, 630, 640, TILE_HEIGHT, 0, page * TILE_HEIGHT, 640, TILE_HEIGHT, 0, SDL_FLIP_NONE);
}
