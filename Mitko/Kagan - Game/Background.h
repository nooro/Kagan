#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <SDL.h>

struct SDL_Background
{
    SDL_Texture* texture;

    bool InitBackground(char* FILE, SDL_Renderer* Rend)
    {
        SDL_Surface* tempSurf = NULL;
        SDL_Texture* tempTexture = NULL;

        if((tempSurf = IMG_Load(FILE)) == NULL)
        {
            printf( "Unable to load background %s! SDL_image Error: %s\n", FILE, IMG_GetError() );

            return false;
        }

        if( (tempTexture = SDL_CreateTextureFromSurface( Rend, tempSurf)) == NULL )
        {
            printf( "Unable to create background texture from %s! SDL Error: %s\n", FILE, SDL_GetError() );

            return false;
        }

        texture = tempTexture;

        SDL_FreeSurface(tempSurf);

        return true;
    }

    void render(SDL_Renderer* Rend)
    {
        if(texture == NULL)
        {
            printf("There is no texture to render\n");
        }

        if(Rend == NULL)
        {
            printf("Invalid renderer\n");
        }

        SDL_RenderCopyEx( Rend, texture, NULL, NULL, 0, NULL, SDL_FLIP_NONE );
    }
};

#endif // BACKGROUND_H_INCLUDED
