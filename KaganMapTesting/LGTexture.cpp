#include "LGTexture.h"

//Constructor
LGTexture::LGTexture()
{
    Texture = NULL; // set Texture to NULL
    width = 0; // set width to 0
    height = 0; // set height to 0
}

//Destructor
LGTexture::~LGTexture()
{
    free(); // calls free
}

// If we have included SDL_TTF for the text initialize texture from text
#ifdef _SDL_TTF_H
bool LGTexture::loadFromRenderedText( std::string textureText, SDL_Renderer* Rend, TTF_Font* font, SDL_Color textColor, int x, int y )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor);

	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        Texture = SDL_CreateTextureFromSurface( Rend, textSurface );

		if( Texture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() ); // if there was an error puts it on the console

			return false; // return false if failed
		}
		else
		{
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;

            screen_x = x;
            screen_y = y;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() ); // if there was an error puts it on the console

		return false; //return false if failed
	}


	return true;
}
#endif


//Load a texture from renderer , file path and position
bool LGTexture::load(SDL_Renderer* LGRenderer, char* FILE, int x, int y)
{
    //Free memory
    free();

    //Creates a surface and sets it to NULL
    SDL_Surface* tempSurf = NULL;
    //Creates a texture and sets it to NULL
    SDL_Texture* tempTexture = NULL;

    //Loads the image to the surface and checks if it failed
    if((tempSurf = IMG_Load(FILE)) == NULL)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", FILE, IMG_GetError() ); // if there was an error puts it on the console

        return false; // return that it failed
    }

	SDL_SetColorKey(tempSurf, SDL_TRUE, SDL_MapRGB( tempSurf->format, 0, 0xFF, 0xFF )); // set color key for the surface

	//Creates a texture from the surface
	if( (tempTexture = SDL_CreateTextureFromSurface( LGRenderer, tempSurf)) == NULL )
	{
		printf( "Unable to create texture from %s! SDL Error: %s\n", FILE, SDL_GetError() ); // if there was an error puts it on the console

		return false; // return that it failed
	}


    width = tempSurf->w; // get the surface width
    height = tempSurf->h; // get the surface height

    screen_x = x; // set the screen width
    screen_y = y; // set the screen height

    Texture = tempTexture; // set the main texture to point to the one we loaded

    SDL_FreeSurface(tempSurf); // free the memory for the surface

    return true;
}

//Frees the memory
void LGTexture::free()
{
	if( Texture != NULL )
	{
		SDL_DestroyTexture( Texture ); // frees the memory for the texture
		Texture = NULL; // sets it to null
		width = 0; // sets width to 0
		height = 0; // and height to 0
	}
}

//Render the texture on given renderer, position, how big to the original,
//what part of the original, in which angle to render, the center of the rotation and the flip of the image
void LGTexture::render(SDL_Renderer* LGRenderer, float x, float y, float scale, SDL_Rect* srcrect, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Check if there is a texture to render
    if(Texture == NULL)
    {
        printf("There is no texture to render\n");  // output if there is no texture
    }

    //Check if the renderer is valid
    if(LGRenderer == NULL)
    {
        printf("Invalid renderer\n"); // output if he is no valid
    }

    //Gets the texture dimension
	SDL_Rect dstrect = { x * screen_x, y * screen_y, width, height };

    //if there is given part of the original set it
	if( srcrect != NULL )
	{
	    // sets the dimensions to render equal to the part to render
		dstrect.w = srcrect->w;
		dstrect.h = srcrect->h;
	}

    // scale the dimensions
	dstrect.w *= scale;
	dstrect.h *= scale;

	// Copies it on the renderer
	SDL_RenderCopyEx( LGRenderer, Texture, srcrect, &dstrect, angle, center, flip );
}

//Returns the width of the texture
int LGTexture::getWidth()
{
	return width;
}

//Return the height of the texture
int LGTexture::getHeight()
{
	return height;
}

//Sets the dimensions of the texture
void LGTexture::set_dimensions(int w, int h)
{
    width = w;
    height = h;
}

//Sets a color mod for the texture with given RGB
void LGTexture::setColorMod( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( Texture, red, green, blue );
}

//Sets a blend mode
void LGTexture::setBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( Texture, blending );
}

//Set alpha of the image , 0 transparent, 255 full
void LGTexture::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( Texture, alpha );
}
