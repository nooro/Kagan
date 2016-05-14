#ifndef LGTEXTURE_H
#define LGTEXTURE_H

/*
    Texture class for easier use of the SDL_Texture
*/

#include "SDL.h" // include SDL
#include "SDL_ttf.h" // include SDL_TTF for text
#include "SDL_image.h" // include SDL_Image for handling png, jpg and more
#include <string> // include string
#include <stdio.h> // for printf and more

//Light game texture
class LGTexture
{
    public:
        //Constructor
        LGTexture();
        //Destructor
        ~LGTexture();

        //Loads an image from file
        bool load(SDL_Renderer* LGRenderer, char* FILE, int x, int y);
        //Define the load from text method if we have included SDL_TTF
        #ifdef _SDL_TTF_H
        bool loadFromRenderedText( std::string textureText, SDL_Renderer* Rend, TTF_Font* font, SDL_Color textColor, int x, int y );
        #endif // _SDL_TTF_H

        //Frees memory
        void free();

        //Renders the image on the screen
        void render( SDL_Renderer* LGRenderer, float x, float y, float scale = 1, SDL_Rect* clip = NULL, double angle = 0.0,
                     SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        //SDL_SetTexture modes
        void setColorMod( Uint8 red, Uint8 green, Uint8 blue );
		void setBlendMode( SDL_BlendMode blending );
		void setAlpha( Uint8 alpha );

        //Returns the width of the texture we loaded
		int getWidth();
        //Returns the height of the texture we loaded
		int getHeight();

		void set_dimensions(int w, int h);

    protected:
    private:

        //The texture we are using
        SDL_Texture* Texture;

        //dimension of the texture
        int width;
        int height;

        //dimension of the screen
        int screen_x;
        int screen_y;
};

#endif // LGTEXTURE_H
