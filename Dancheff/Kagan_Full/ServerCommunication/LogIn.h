#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

class LogIn
{
public:
    LogIn(); //Initialize everything for the log-in. Create log-in window with fields to enter user-name and password. Send the data to the server.
    ~LogIn(); //Free the used memory.
    char Status(); //Return if the log-in is successful or not.

private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    SDL_Texture *backgroundTexture = NULL;

    bool logInWindowIsActive;
    void Loop();
    void CheckForEvents();
};

#endif // LOGIN_H_INCLUDED
