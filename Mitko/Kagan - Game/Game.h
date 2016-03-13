#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <Entity.h>
#include "Background.h"
#include "GUIBars.h"
#include "DMGText.h"
using namespace std;

class Game
{
private:
    int WINDOW_MAX_WIDTH;
    int WINDOW_MAX_HEIGHT;

    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
    bool gameIsRunning = true;

    void LoadTheResources();
    void GameLoop();
    void CheckForEvents();
    void Render();
    void Exit();

    SDL_Background background;
    Entity character;

    bar health_bar, stamina_bar;
    dmgFloat dmgtxt;
    SDL_Color White = {255, 255, 255, 255};

public:
    Game();
    void Run(string username);

};

#endif // GAME_H
