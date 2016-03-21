#ifndef TILE_H
#define TILE_H

#include "Includes.h"
#include "Camera.h"

#define TILE_WIDTH 64
#define TILE_HEIGHT 64

class TILE
{
    public:
        TILE();
        virtual ~TILE();

        int xCoord; // X of the matrix
        int yCoord; // Y of the matrix
        int tileProperty; // Tile Properties : 0 for disabled 1 from ground
        int tileSetCoordX; // Coordinates of the image from the tile set
        int tileSetCoordY; // Coordinates of the image from the tile set
        int tileSetY; // Columns of the tile set
        double angle; // The rotation of the tile

        void DrawTile(SDL_Renderer* Rend, Camera* cam, SDL_Texture* TileTemp);
        void LoadTile(int x, int y, int prop, int xImg);//, int layer);

        void MakeIso();
        bool hoverTile(int Mx, int My, Camera* cam);

    protected:
    private:
};

#endif // TILE_H
