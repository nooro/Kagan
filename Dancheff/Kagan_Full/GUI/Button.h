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
    Button();
    void SetText(char *text, TTF_Font *font, SDL_Renderer *renderer);
    void Render(SDL_Renderer *renderer);
    void RenderHover(SDL_Renderer *renderer);

private:
    SDL_Texture *buttonText;
    TTF_Font *buttonFont;
    SDL_Color buttonTextColor;
};

#endif // BUTTON_H_INCLUDED
