#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL.h>
#include <iostream>
using namespace std;

class Game
{
public:
    Game(); //Initialize everything for the game
    ~Game(); //Free the used memory
    void Run(string username); // Run the game for the logged-in client

private:
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
    SDL_Event event;

    bool gameIsRunning;
    int windowWidth, windowHeight;

    void LoadTheResources();
    void GameLoop();
    void CheckForEvents();
    void Render();
    //void FreeTheTextures();
};

#endif // GAME_H_INCLUDED
