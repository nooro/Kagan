#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "GUI.h"
#include "../General/General.h"
#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>
using namespace std;

class Button : public GUI
{
public:
    void SetText(char *text, string fontPath, int fontSize, SDL_Renderer *renderer);
    void Render(SDL_Renderer *renderer);
    void RenderHover(SDL_Renderer *renderer);

private:
    SDL_Texture *buttonText;
};

#endif // BUTTON_H_INCLUDED
