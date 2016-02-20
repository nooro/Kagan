#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
using namespace std;

class Game
{
private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;

    bool gameIsRunning = true;
public:
    Game();
    void Run(string username);
    void LoadTheResources();
    void GameLoop();
    void CheckForEvents();
};

#endif // GAME_H
