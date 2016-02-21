#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
using namespace std;

class Game
{
private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    bool gameIsRunning = true;

    void LoadTheResources();
    void GameLoop();
    void CheckForEvents();

public:
    Game();
    void Run(string username);
};

#endif // GAME_H
