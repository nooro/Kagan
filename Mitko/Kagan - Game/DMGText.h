#ifndef DMGTEXT_H_INCLUDED
#define DMGTEXT_H_INCLUDED

#include <sstream>
#include <string>

using namespace std;

struct dmgFloat
{
    SDL_Color textColor;
    LGTexture floatText;
    TTF_Font* font;
    int screen_x;
    int screen_y;

    int alpha = 255;
    bool exist = false;

    int fading = 20;
    float ascending = 0.005;

    float x;
    float y;

    void init(char* file, int font_size, SDL_Color color, int scrx_, int scry_)
    {
        font = TTF_OpenFont( file, font_size );
        if( font == NULL )
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        }

        textColor = color;

        screen_x = scrx_;
        screen_y = scry_;
    }

    void floating()
    {
        floatText.setAlpha(alpha);
        alpha -= fading;
        y -= ascending;

        if(alpha <= 0)
        {
            exist = false;
            alpha = 255;
        }
    }

    void render(SDL_Renderer* Rend)
    {
        if(exist == false)
            return;

        floating();
        floatText.render(Rend, x, y);
    }

    void load(SDL_Renderer* Rend, int dmg, float x_, float y_)
    {
        std::string text;
        ostringstream convert;
        convert << dmg;
        text = convert.str();

        x = x_;
        y = y_;

        exist = true;
        floatText.loadFromRenderedText(text, Rend, font, textColor, screen_x, screen_y);
    }

    void setFade(int fading_)
    {
        fading = fading_;
    }

    void setAscend(float ascending_)
    {
        ascending = ascending_;
    }
};

#endif // DMGTEXT_H_INCLUDED
