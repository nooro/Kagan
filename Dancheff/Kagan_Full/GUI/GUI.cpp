#include "GUI.h"

GUI::GUI()
{
    rect.x = 0; rect.y = 0;
    rect.w = 0; rect.h = 0;
    texture = NULL;
    hoverTexture = NULL;
    SDL_GetMouseState(&mouseX, &mouseY);
}

GUI::~GUI()
{
    delete(&rect);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(hoverTexture);
}

bool GUI::isClicked(SDL_Event *event)
{
    if(event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT)
        return this->isHover();
    return false;
}

bool GUI::isHover()
{
    SDL_GetMouseState(&mouseX, &mouseY);
    return mouseX >= rect.x && mouseX <= rect.x + rect.w
        && mouseY >= rect.y && mouseY <= rect.y + rect.h ;
}

int GUI::GetX() { return rect.x; }
int GUI::GetY() { return rect.y; }
int GUI::GetWidth() { return rect.w; }
int GUI::GetHeight() { return rect.h; }

void GUI::SetHeight(int height) { rect.h = height; }
void GUI::SetWidth(int width) { rect.w = width; }
void GUI::SetX(int x) { rect.x = x; }
void GUI::SetY(int y) { rect.y = y; }

void GUI::SetTexture(SDL_Texture *texture) { this->texture = texture; }
void GUI::SetHoverTexture(SDL_Texture *hoverTexture) { this->hoverTexture = hoverTexture; }
