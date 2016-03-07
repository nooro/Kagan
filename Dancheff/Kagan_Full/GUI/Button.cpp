#include "Button.h"

void Button::SetText(char *text, string fontPath, int fontSize, SDL_Renderer *renderer)
{
    buttonText = CreateTextTexture(renderer, text, fontPath, fontSize);
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
