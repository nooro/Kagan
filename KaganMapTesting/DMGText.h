#ifndef DMGTEXT_H_INCLUDED
#define DMGTEXT_H_INCLUDED

#include <SDL.h> // include SDL
#include <SDL_ttf.h> // include SDL_TTF for text use
#include "LGTexture.h" // include LGTexture class see header for more info
#include <sstream> // for string stream to convert
#include <string> // regular string
#include <list> // list for keeping all the dmg texts in the game
#include <iostream>

using namespace std;

struct dmgFloat
{

    dmgFloat(); //Constructor
    dmgFloat(const dmgFloat& other); // Copy constructor
    ~dmgFloat(); // Destructor

    SDL_Color textColor; // the color of the text
    LGTexture floatText; // the texture for the text read LGTexture.h for more info
    TTF_Font* font; // the font
    int screen_x; // window dimensions
    int screen_y;
    float colorMod; // color mod ... read in the implementation

    int alpha; // integer for the alpha
    bool exist; // keeps if the text exist or not , if it does not it gets deleted later
    string text; // string for the text for the texture

    int fading = 20; // fade rate
    float ascending = 0.005; // ascend rate

    float x; // x position
    float y; // y position

    //Initialize the damage float text with given path, size, color and window dimensions
    void init(char* file, int font_size, SDL_Color color, int scrx_, int scry_);
    void floating(); // make the text float and fade
    void render(SDL_Renderer* Rend); // render the text
    void load(int dmg, float x_, float y_); // load a damage text from a damage int
    void setFade(int fading_); // sets the fade rate
    void setAscend(float ascending_); // sets the ascend rate

};

#endif // DMGTEXT_H_INCLUDED
