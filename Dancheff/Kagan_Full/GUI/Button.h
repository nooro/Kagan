#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "GUI.h"
#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>
using namespace std;

class Button : public GUI
{
public:
    void SetText(string text);
private:
};

#endif // BUTTON_H_INCLUDED
