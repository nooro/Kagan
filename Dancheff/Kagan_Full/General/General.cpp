#include "General.h"

string User::username = "";
string User::password = "";

int screenHeight;
int screenWidth;

void InitEverythingGeneral()
{
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

int GetScreenHeight()
{
    return screenHeight;
}

int GetScreenWidth()
{
    return screenWidth;
}


SDL_Texture *CreateTexture(std::string filePath, SDL_Renderer* textureRenderer){
    SDL_Texture* texture = NULL;
    SDL_Surface* temp_surface = IMG_Load(filePath.c_str());

    texture = SDL_CreateTextureFromSurface(textureRenderer, temp_surface);
    SDL_FreeSurface(temp_surface);
    return texture;
}

SDL_Texture *CreateTextTexture(SDL_Renderer* renderer, std::string text, TTF_Font *font, SDL_Color textColor)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return textTexture;
}
