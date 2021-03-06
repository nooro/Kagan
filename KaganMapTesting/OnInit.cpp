#include "Game.h"
#include "Map.h"

bool Game::OnInit()
{
    //Initialize everything in SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    if( TTF_Init() < 0 ) // Initialize SDL_TTF for the text
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() ); // if there is an error catch it and prints on the console
    }

    //Creating Window             title ,Xpos,Ypos,Width,Height, settings
    if((Window = SDL_CreateWindow("Blank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MIN_WINDOW_X, MIN_WINDOW_Y,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP)) == NULL)
    {
        return false;
    }

    SDL_SetWindowMaximumSize(Window, MAX_WINDOW_X, MAX_WINDOW_Y);
    SDL_SetWindowMinimumSize(Window, MIN_WINDOW_X, MIN_WINDOW_Y);

    SDL_GetWindowSize(Window, &WindowWidth, &WindowHeight);

    Fullscreen = false;

    if((Icon = IMG_Load("./Resources/Images/favicon.png")) == NULL)
    {
        cout<<"Icon not loaded"<<endl;
        return false;
    }

    SDL_SetWindowIcon(Window, Icon);

    // Creating Renderer
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //Check Renderer
    if(Renderer == NULL)
    {
        cout << SDL_GetError() << endl;
        return false;
    }

    //Creating Entities

    if( (Cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND)) == NULL)
    {
        return false;
    }

    if( (DragCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL)) == NULL)
    {
        return false;
    }

    //Load Images

    if(LoadContent() == false)
    {
        cout<<"Load content failed"<<endl;
        return false;
    }

    Character.CreateEntity(0, 0, 150, 120);
    HitMark.CreateEntity(0, 0, 96, 96);

    for(int i = 0; i < 5; i ++)
        Enemy[i].CreateEnemy(100, 2, 4, 250, 25); // flying
    for(int i = 5; i < 10; i ++)
        Enemy[i].CreateEnemy(60, 4, 1, 600, 10); // spidey

    Enemy[0].CreateEntity(300, 300, 112, 112);
    Enemy[1].CreateEntity(700, 700, 112, 112);
    Enemy[2].CreateEntity(1000, 1300, 112, 112);
    Enemy[3].CreateEntity(400, 900, 112, 112);
    Enemy[4].CreateEntity(700, 900, 112, 112);
    Enemy[5].CreateEntity(1400, 1400, 120, 100);
    Enemy[6].CreateEntity(1000, 2200, 120, 100);
    Enemy[7].CreateEntity(400, 1300, 120, 100);
    Enemy[8].CreateEntity(100, 900, 120, 100);
    Enemy[9].CreateEntity(900, 700, 120, 100);


    LoadMap("./Resources/Maps/Mapv1.map");

    return true;
}

SDL_Texture* Game::OnLoad(SDL_Renderer* Rend, char* File)
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

void Game::LoadLayer(string file)
{
    Map temp;
    temp.Tileset_Image = OnLoad(Renderer, TILESET);
    temp.Hover_Image = OnLoad(Renderer, TILESET);
    string path = "./Resources/Maps/";
    path.append(file);

    temp.loadMap.open(path);

    if(temp.LoadTileSet() == false)
    {
        cout << "A temp layer failed to load"<<endl;
        Running = false;
    }

    layer.push_back(temp);

    temp.loadMap.close();

}

void Game::LoadMap(char* map_file)
{
    Map::layer = 0;
    layer.clear();

    ifstream mapfile;

    mapfile.open(map_file);

    string layerFile;

    int i = 0;

    while(!mapfile.eof())
    {
        mapfile >> layerFile;
        cout << layerFile <<endl;
        cout << " "<<Map::layer<<endl;
        LoadLayer(layerFile);
        Map::layer++;
    }

    layer.pop_back();
    Map::layer--;

    mapfile.close();
}

