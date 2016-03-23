#include "Button.h"

Button::Button()
{
    buttonFont = TTF_OpenFont("Resources/Fonts/Chiller.ttf", 20);
}

void Button::SetText(char *text, TTF_Font *font, int fontSize, SDL_Renderer *renderer)
{
    buttonText = CreateTextTexture(renderer, text, font, fontSize, buttonTextColor);
}

void Button::Render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderCopy(renderer, buttonText, NULL, &rect);
}

void Button::RenderHover(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, hoverTexture, NULL, &rect);
    SDL_RenderPresent(renderer);
}
