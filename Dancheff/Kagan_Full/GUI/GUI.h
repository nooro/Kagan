#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <SDL.h>
#include <iostream>
using namespace std;

class GUI
{
public:
    GUI();
    ~GUI();

    int GetX();
    int GetY();
    int GetWidth();
    int GetHeight();

    void SetX(int x);
    void SetY(int y);
    void SetWidth(int width);
    void SetHeight(int height);

    void SetTexture(SDL_Texture *texture);
    void SetHoverTexture(SDL_Texture *hoverTexture);

    bool isHover();
    bool isClicked(SDL_Event *event);

protected:
    SDL_Rect rect;
    SDL_Texture *texture;
    SDL_Texture *hoverTexture;

    int mouseX, mouseY;
};

#endif // GUI_H_INCLUDED
