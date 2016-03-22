#ifndef MAP_H
#define MAP_H

#include "TILE.h"
#include "Includes.h"

#define MAP_X 100
#define MAP_Y 100

class Map
{
    public:
        Map();
        Map( const Map& other );

        ifstream loadMap;
        ofstream saveMap;

        bool building;
        static int selectedTileX;
        static int selectedTileY;
        int page;
        static int layer;
        int mylayer;


        static TILE* hoverTile;

        TILE tile_map[MAP_X][MAP_Y];

        SDL_Texture* Tileset_Image;
        SDL_Texture* Hover_Image;

        TILE* GetHoverTile(Camera* cam);

        bool LoadTileSet();
        bool SaveMap(string name);
        bool OnHover(SDL_Renderer* Rend, Camera* cam);

        void RenderMap(SDL_Renderer* Rend, Camera* cam);
        void DrawTileList(SDL_Renderer* Rend, Camera* cam);
        void ChangeTile();
        void PlaceTile();
        void DeleteTile();
        void SetLayer();
        void LowerLayer();




    protected:
    private:
};

#endif // MAP_H
