#include "LGTexture.h"

LGTexture::LGTexture(int x, int y)
{
    Texture = NULL;
    width = 0;
    height = 0;
    screen_x = x;
    screen_y = y;
}

LGTexture::~LGTexture()
{
    free();
}

bool LGTexture::load(SDL_Renderer* LGRenderer, char* FILE)
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

	//SDL_RenderCopyEx( LGRenderer, Texture, srcrect, &dstrect, angle, center, flip );
	SDL_RenderCopy( LGRenderer, Texture, srcrect, &dstrect);
}

int LGTexture::getWidth()
{
	return width;
}

int LGTexture::getHeight()
{
	return height;
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
