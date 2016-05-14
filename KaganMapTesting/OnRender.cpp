#include "Game.h"

void Game::OnRender()
{
    SDL_RenderClear(Renderer);
    cout << Character.rotation <<endl;
    cout << layer.size() <<endl;

    SDL_GetWindowSize(Window, &WindowWidth, &WindowHeight);

    for (list<Map>::iterator it = layer.begin(); it != layer.end(); it++)
    {
        it->RenderMap(Renderer, &Camera1, WindowWidth, WindowHeight);
    }

    First.DrawEntity(Renderer, &Camera1);

    Camera1.camX = -(Character.XPos - WindowWidth / 2 + Character.Width / 2);
    Camera1.camY = -(Character.YPos - WindowHeight / 2 + Character.Height / 2);

    switch(Character.action)
    {
        case Character.IDLE:
            Character.Animate(Renderer, &Camera1, &Idle[Character.rotation]);
            break;
        case Character.WALK:
            Character.AnimateBackwards(Renderer, &Camera1, &Walk[Character.rotation]);
            break;
        case Character.ATACK:
            Character.AnimateBackwards(Renderer, &Camera1, &Atack[Character.rotation], 1.10);
            if(Atack[Character.rotation].currentFrame > 15 && Atack[Character.rotation].currentFrame < 20)
                HitMark.Animate(Renderer, &Camera1, &Spark);

            for(int i = 0; i < 10; i++)
                cout <<"HERE  "<< Atack[Character.rotation].currentFrame <<endl;
            break;
        default:
            Character.Animate(Renderer, &Camera1, &Idle[Character.rotation]);
            break;
    }

    health_bar.render(Renderer); // render the health bar
    list<dmgFloat>::iterator it = dmg_text.begin(); // iterator for the list of damage texts
    while(it != dmg_text.end() && dmg_text.size() > 0) // iterate trough all of them
    {
        if(!it->exist) // if it does not exist erase it from the list
            dmg_text.erase(it++);
        else // if it does
        {
            it->render(Renderer); //render it
            ++it; // move to the next one
        }
    }

    SDL_SetTextureAlphaMod(Thanks, 100);

    if(Character.alive == false)
        Draw(Renderer, &Camera1, Thanks, 0 - Camera1.camX, 0 - Camera1.camY, WindowWidth, WindowHeight, 0, SDL_FLIP_NONE);


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
