#ifndef INPUTFIELD_H_INCLUDED
#define INPUTFIELD_H_INCLUDED

#include "GUI.h"
#include "../General/General.h"
#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>
using namespace std;

class InputField : public GUI
{
public:
    InputField(SDL_Renderer *render);
    ~InputField();

    string type;

    void Render();
    void RenderHover();

    void Input(SDL_Event *e);

    string GetInputText();
    bool isActive;

    void SetCharLimit(int limit);
    void SetTextColor(int r, int g, int b, int a);

private:
    SDL_Renderer *render = NULL;
    SDL_Texture *inputFieldTexture;

    SDL_Color textColor;
    TTF_Font *font = NULL;
    SDL_Texture *inputTexture = NULL;
    string inputText;
    int charLimit;
};

#endif // INPUTFIELD_H_INCLUDED
