#ifndef LGTEXTURE_H
#define LGTEXTURE_H

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <stdio.h>

//Light game texture
class LGTexture
{
    public:
        //Constructor
        LGTexture(int x, int y);
        //Destructor
        ~LGTexture();

        //Loads an image from file
        bool load(SDL_Renderer* LGRenderer, char* FILE);

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

    protected:
    private:

        //The texture we are using
        SDL_Texture* Texture;

        int width;
        int height;

        int screen_x;
        int screen_y;
};

#endif // LGTEXTURE_H
