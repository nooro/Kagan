#include "DMGText.h"

//Constructor
dmgFloat::dmgFloat()
{

}

//Copy constructor
dmgFloat::dmgFloat(const dmgFloat& other)
{
    this->exist = true; // set exist to true
    this->alpha = 255; // set alpha to 255 / max
    this->font = other.font; // set the font

    this->screen_x = other.screen_x; // set screen width
    this->screen_y = other.screen_y; // set screen height
    this->x = other.x; // set starting coordinates
    this->y = other.y; // set starting coordinates

    this->ascending = other.ascending; // set ascending speed
    this->fading = other.fading; // set speed of fading

    this->textColor = other.textColor; // set the text color
    this->text = other.text; // set the text messages
    this->colorMod = other.colorMod; // set color mode
}

//Destructor
dmgFloat::~dmgFloat()
{

}

//Initialize with given path , font size, color , screen width and screen height
void dmgFloat::init(char* file, int font_size, SDL_Color color, int scrx_, int scry_)
{
    //Load the fond with path and size
    font = TTF_OpenFont( file, font_size );
    if( font == NULL ) // check if it loaded
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() ); // if it failed prints error on the console
    }

    textColor = color; // set the color

    screen_x = scrx_; // set the width of screen
    screen_y = scry_; // set the height of screen
}

//Make the text float and fade
void dmgFloat::floating()
{
    this->alpha -= this->fading; // take out given amount of the alpha
    this->y -= this->ascending; // ascend the text with given value

    if(this->alpha <= 0) // if the alpha is lower than 0
    {
        exist = false; // set to non existing which will delete it from the vector later
        alpha = 255; // and set the alpha to max for later use
    }
}

void dmgFloat::render(SDL_Renderer* Rend)
{
    if(exist == false) // if it does not exist there is an error so return
        return;
    if(text.empty()) // if the text is empty there is an error so return
        return;

    //Loads the texture with the given text, font, color and screen dimension
    floatText.loadFromRenderedText(text, Rend, font, textColor, screen_x, screen_y);
    floatText.setColorMod(255, colorMod, colorMod); // set the color mod
    floatText.setAlpha(alpha); // set the alpha

    floatText.render(Rend, x, y); // render the text
    floating(); // and make it float
}

//Load a damage floating text with given damage and starting position
void dmgFloat::load(int dmg, float x_, float y_)
{
    // set the color mod depending on the dmg (the higher the dmg the more red it gets)
    // and on 0 its white
    colorMod = 255 - (dmg / 100.f) * 255;

    x = x_; // set the x position
    y = y_; // set the y position

    ostringstream convert; // string stream for converting int to sting
    convert << dmg; // we put the int into the stream
    text = convert.str(); // and convert it to normal string for later use
}

//Set the fade
void dmgFloat::setFade(int fading_)
{
    fading = fading_;
}

//Set the ascend
void dmgFloat::setAscend(float ascending_)
{
    ascending = ascending_;
}
