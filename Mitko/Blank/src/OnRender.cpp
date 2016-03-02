#include "Game.h"

void Game::OnRender()
{
    SDL_RenderClear(Renderer);
    cout << Rotation <<endl;


    //Render the map
    Map1.RenderMap(Renderer, &Camera1);
    //Map2.RenderMap(Renderer, &Camera1);
    //Map3.RenderMap(Renderer, &Camera1);
   // Character.Animate(Renderer, &Camera1, &Idle[Rotation]);



    SDL_RenderPresent(Renderer);
}

/// Draw Functions ...

bool Game::Draw(SDL_Renderer* Rend,
                Camera* cam,
                SDL_Texture* Temp,
                int x, int y, int w, int h,
                double angle,
                SDL_RendererFlip Flip)
{
    //Rectangle for Position
    SDL_Rect dstrect;

    //Texture is empty
    if(Temp == NULL)
    {
        return false;
    }

    dstrect.x = x + cam->camX;
    dstrect.y = y + cam->camY;
    dstrect.w = w * cam->camZoom;
    dstrect.h = h * cam->camZoom;

    //Draw on the screen
	SDL_RenderCopyEx(Rend, Temp, NULL, &dstrect, angle, NULL, Flip);

	return true;
}

bool Game::Draw(SDL_Renderer* Rend,
                Camera* cam,
                SDL_Texture* Temp,
/*Location*/    int x, int y, int w, int h,
/*  Part  */    int x2, int y2, int w2, int h2,
                double angle,
                SDL_RendererFlip Flip)
{
    //Rectangle for position
    SDL_Rect dstrect;
    //Rectangle for part of an image
    SDL_Rect srtrect;

    //Texture is empty
    if(Temp == NULL)
    {
        return false;
    }

    dstrect.x = x + cam->camX;
    dstrect.y = y + cam->camY;
    dstrect.w = w * cam->camZoom;
    dstrect.h = h * cam->camZoom;

    srtrect.x = x2;
    srtrect.y = y2;
    srtrect.w = w2;
    srtrect.h = h2;


    //Draw on the screen
	SDL_RenderCopyEx(Rend, Temp, &srtrect, &dstrect, angle, NULL, Flip);

	return true;
}
