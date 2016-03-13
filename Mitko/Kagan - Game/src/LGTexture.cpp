#include "LGTexture.h"

LGTexture::LGTexture()
{
    Texture = NULL;
    width = 0;
    height = 0;
}

LGTexture::~LGTexture()
{
    free();
}

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
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );

			return false;
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
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );

		return false;
	}


	return true;
}
#endif

bool LGTexture::load(SDL_Renderer* LGRenderer, char* FILE, int x, int y)
{
    free();

    SDL_Surface* tempSurf = NULL;
    SDL_Texture* tempTexture = NULL;

    if((tempSurf = IMG_Load(FILE)) == NULL)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", FILE, IMG_GetError() );

        return false;
    }

	SDL_SetColorKey(tempSurf, SDL_TRUE, SDL_MapRGB( tempSurf->format, 0, 0xFF, 0xFF ));

	if( (tempTexture = SDL_CreateTextureFromSurface( LGRenderer, tempSurf)) == NULL )
	{
		printf( "Unable to create texture from %s! SDL Error: %s\n", FILE, SDL_GetError() );

		return false;
	}


    width = tempSurf->w;
    height = tempSurf->h;

    screen_x = x;
    screen_y = y;

    Texture = tempTexture;

    SDL_FreeSurface(tempSurf);

    return true;
}

void LGTexture::free()
{
	if( Texture != NULL )
	{
		SDL_DestroyTexture( Texture );
		Texture = NULL;
		width = 0;
		height = 0;
	}
}

void LGTexture::render(SDL_Renderer* LGRenderer, float x, float y, float scale, SDL_Rect* srcrect, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    if(Texture == NULL)
    {
        printf("There is no texture to render\n");
    }

    if(LGRenderer == NULL)
    {
        printf("Invalid renderer\n");
    }

	SDL_Rect dstrect = { x * screen_x, y * screen_y, width, height };

	if( srcrect != NULL )
	{
		dstrect.w = srcrect->w;
		dstrect.h = srcrect->h;
	}

	dstrect.w *= scale;
	dstrect.h *= scale;

	SDL_RenderCopyEx( LGRenderer, Texture, srcrect, &dstrect, angle, center, flip );
}

int LGTexture::getWidth()
{
	return width;
}

int LGTexture::getHeight()
{
	return height;
}

void LGTexture::set_dimensions(int w, int h)
{
    width = w;
    height = h;
}

void LGTexture::setColorMod( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( Texture, red, green, blue );
}

void LGTexture::setBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( Texture, blending );
}

void LGTexture::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( Texture, alpha );
}
