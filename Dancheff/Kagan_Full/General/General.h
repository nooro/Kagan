#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

void InitEverythingGeneral();

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <windows.h>

SDL_Texture *CreateTexture(std::string filePath, SDL_Renderer* textureRenderer);

int GetScreenHeight();
int GetScreenWidth();

#endif // GENERAL_H_INCLUDED
