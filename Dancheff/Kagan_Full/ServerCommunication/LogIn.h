#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

#include <SDL.h>
#include <iostream>
using namespace std;

class LogIn
{
public:
    LogIn(); //Initialize everything for the log-in
    ~LogIn(); //Free the used memory

private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
};

#endif // LOGIN_H_INCLUDED
