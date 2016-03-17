#include "DMGText.h"

dmgFloat::dmgFloat()
{

}

dmgFloat::dmgFloat(const dmgFloat& other)
{
    this->exist = true;
    this->alpha = 255;
    this->font = other.font;

    this->screen_x = other.screen_x;
    this->screen_y = other.screen_y;
    this->x = other.x;
    this->y = other.y;

    this->ascending = other.ascending;
    this->fading = other.fading;

    this->textColor = other.textColor;
    this->text = other.text;
    this->colorMod = other.colorMod;
}

dmgFloat::~dmgFloat()
{

}

void dmgFloat::init(char* file, int font_size, SDL_Color color, int scrx_, int scry_)
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

void dmgFloat::floating()
{
    this->alpha -= this->fading;
    this->y -= this->ascending;

    if(this->alpha <= 0)
    {
        exist = false;
        alpha = 255;
    }
}

void dmgFloat::render(SDL_Renderer* Rend)
{
    if(exist == false)
        return;
    if(text.empty())
        return;


    floatText.loadFromRenderedText(text, Rend, font, textColor, screen_x, screen_y);
    floatText.setColorMod(255, colorMod, colorMod);
    floatText.setAlpha(alpha);

    floatText.render(Rend, x, y);
    floating();
}

void dmgFloat::load(int dmg, float x_, float y_)
{
    colorMod = 255 - (dmg / 100.f) * 255;

    x = x_;
    y = y_;


    ostringstream convert;
    convert << dmg;
    text = convert.str();
}

void dmgFloat::setFade(int fading_)
{
    fading = fading_;
}

void dmgFloat::setAscend(float ascending_)
{
    ascending = ascending_;
}
