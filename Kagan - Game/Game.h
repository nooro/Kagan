#ifndef GAME_H
#define GAME_H

#include "LGTexture.h"
#include <SDL.h>
#include <iostream>
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

    LGTexture test = LGTexture(WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT);

public:
    Game();
    void Run(string username);

};

#endif // GAME_H
