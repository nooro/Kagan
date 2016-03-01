#include "GUI.h"

GUI::GUI()
{
    x = 0; y = 0;
    w = 0; h = 0;
    texture = NULL;
    hoverTexture = NULL;
}

GUI::~GUI()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(hoverTexture);
}

bool GUI::isClicked()
{
    if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if(event.button.x >= x && event.button.x <= x + w)
            {
                if(event.button.y >= y && event.button.y <= y + h)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool GUI::isHovered()
{
    int *mouseX, *mouseY;
    SDL_GetMouseState(mouseX, mouseY);

    if(*mouseX >= x && *mouseX <= x + w)
    {
        if(*mouseY >= y && *mouseY <= y+h)
        {
            return true;
        }
    }
    return false;
}

int GUI::GetX() { return x; }
int GUI::GetY() { return y; }
int GUI::GetWidth() { return w; }
int GUI::GetHeight() { return h; }

void GUI::SetHeight(int height) { h = height; }
void GUI::SetWidth(int width) { w = width; }
void GUI::SetX(int x) { this->x = x; }
void GUI::SetY(int y) { this->y = y; }

void GUI::SetTexture(SDL_Texture *texture) { this->texture = texture; }
void GUI::SetHoverTexture(SDL_Texture *hoverTexture) { this->hoverTexture = hoverTexture; }
