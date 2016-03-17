#ifndef DMGTEXT_H_INCLUDED
#define DMGTEXT_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include "./include/LGTexture.h"
#include <sstream>
#include <string>
#include <list>
#include <iostream>

using namespace std;

struct dmgFloat
{
    dmgFloat();
    dmgFloat(const dmgFloat& other);
    ~dmgFloat();

    SDL_Color textColor;
    LGTexture floatText;
    TTF_Font* font;
    int screen_x;
    int screen_y;
    float colorMod;

    int alpha;
    bool exist;
    string text;

    int fading = 20;
    float ascending = 0.005;

    float x;
    float y;

    void init(char* file, int font_size, SDL_Color color, int scrx_, int scry_);
    void floating();
    void render(SDL_Renderer* Rend);
    void load(int dmg, float x_, float y_);
    void setFade(int fading_);
    void setAscend(float ascending_);

};

#endif // DMGTEXT_H_INCLUDED
