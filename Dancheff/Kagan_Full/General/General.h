#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

void InitEverythingGeneral();

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <windows.h>

SDL_Texture *CreateTexture(std::string filePath, SDL_Renderer* textureRenderer);
SDL_Texture *CreateTextTexture(SDL_Renderer* renderer, char *text, std::string fontPath, int fontSize);

int GetScreenHeight();
int GetScreenWidth();

#endif // GENERAL_H_INCLUDED
