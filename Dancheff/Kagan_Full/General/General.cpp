#include "General.h"

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
