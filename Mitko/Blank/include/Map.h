#ifndef MAP_H
#define MAP_H

#include "TILE.h"
#include "Includes.h"

#define MAP_X 32
#define MAP_Y 32

class Map
{
    public:
        Map();
        virtual ~Map();

        ifstream loadMap;
        ofstream saveMap;

        bool building;
        int selectedTileX;
        int selectedTileY;
        int page;

        TILE* hoverTile;

        TILE tile_map[MAP_X][MAP_Y];

        SDL_Texture* Tileset_Image;
        SDL_Texture* Hover_Image;

        TILE* GetHoverTile(Camera* cam);

        bool LoadTileSet(int layer);
        bool SaveMap();
        bool OnHover(SDL_Renderer* Rend, Camera* cam);
        void SetLayer(int layer);
        void RenderMap(SDL_Renderer* Rend, Camera* cam);





    protected:
    private:
};

#endif // MAP_H
