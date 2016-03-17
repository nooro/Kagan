#ifndef GAME_H
#define GAME_H

/*
    The main game class
    from here we control everything in our game
*/

#include <SDL.h> // include SDL
#include <SDL_ttf.h> // include SDL_TTF
#include <iostream> // for cout and more
#include <Entity.h> // include Entities
#include "Background.h" // include background struct
#include "GUIBars.h" // include bars struct
#include "DMGText.h" // include floating text struct
using namespace std;

class Game
{
private:
    //Integer for the width of the screen
    int WINDOW_MAX_WIDTH;
    //Integer for the height of the screen
    int WINDOW_MAX_HEIGHT;

    //Our Renderer for the game
    SDL_Renderer* renderer;
    //Our main game window
    SDL_Window* window;
    //For handling events
    SDL_Event event;
    //While game is running
    bool gameIsRunning = true;

    void LoadTheResources(); // load the game resources
    void GameLoop(); // Main game loop
    void CheckForEvents(); //Check if there is a user input
    void Render(); // Render everything on the screen
    void Exit(); // Exit the game

    SDL_Background background; // Our background texture
    Entity character; // Entity for the character

    bar health_bar; // Health bar for the character
    dmgFloat dmgtxt; // single floating text to copy in to the vector
    list<dmgFloat> dmg_text; // vector of all the floating text
    SDL_Color White = {255, 255, 255, 255}; // Creates a white color

public:
    Game(); // Constructor
    void Run(string username); // Execute the game with the user name of the logged in client

};

#endif // GAME_H
