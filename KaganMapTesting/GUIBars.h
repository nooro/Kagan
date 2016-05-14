#ifndef GUIBARS_H_INCLUDED
#define GUIBARS_H_INCLUDED

/*
    Struct for a bar visualizing some kind of currency
    (like health)
*/

#include "LGTexture.h"

struct bar
{
    private:

        LGTexture texture; // texture for the bar border
        LGTexture textureFill; // texture for the bar filling
        float x; // x position
        float y; // y position
        float scale; // scale to actual texture
        int window_x; // window width
        int window_y; // window height
        float currency = 100; // the currency set on max


    public:

        //Initialize the bar using path , window dimensions , position and scale
        void init(char* texture_file, SDL_Renderer* Rend, int screen_x, int screen_y, float x_, float y_, float scale_ = 1)
        {
            texture.load(Rend, texture_file, screen_x, screen_y); // loads a border from the file
            textureFill.load(Rend, "./Resources/Images/fill.png", screen_x, screen_y); //load the fill of bar
            x = x_; // set position
            y = y_; // set position
            scale = scale_; // set scale
            window_x = screen_x; // set window width
            window_y = screen_y; // set window height
        }

        //Render the bar
        void render(SDL_Renderer* Rend)
        {
            float currency_percent = currency / 100; // calculate percent filled

            // set the fill dimension
            float fillX = x + 0.04 * texture.getWidth() / window_x;
            float fillY = y  + 0.08 * texture.getHeight() / window_y;
            float fillW = texture.getWidth() * 0.94;
            float fillH = texture.getHeight() * 0.35;

            fillW *= currency_percent; // set the width of the fill using the percent filled

            textureFill.set_dimensions(fillW, fillH); // sets the new dimensions

            if(currency_percent < 0.5) // if you are lower than 50%
                textureFill.setColorMod(255, currency_percent / 0.5 * 255, 0); // set a red mod and lower green depending on percent
            if(currency_percent >= 0.5) // if you are higher than 50%
                textureFill.setColorMod((1 - currency_percent) / 0.5 * 255, 255, 0); // set a green mod and lower red depending on percent

            textureFill.render(Rend, fillX, fillY, scale); //render the bar fill
            texture.render(Rend, x, y, scale); // render the bar border
        }

        //Sets a new currency for the bar to visualize
        void setCurrency(float currency_)
        {
            currency = currency_;
        }

};

#endif // GUIBARS_H_INCLUDED
