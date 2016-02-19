#include "Client.h"

void Client::OnEvent(SDL_Event* Event)
{
    if(Event->type == SDL_QUIT)
    {
        Running = false;
    }

    if(Event->type == SDL_WINDOWEVENT)
    {
        if(Event->window.event == SDL_WINDOWEVENT_RESIZED)
        {

        }
    }

    if(Event->type == SDL_KEYDOWN)
    {
        if(Event->key.keysym.sym == SDLK_ESCAPE)
        {
            Running = false;
        }

        if(Event->key.keysym.sym == SDLK_F11)
        {

        }

        if(Event->key.keysym.sym == SDLK_LEFT)
        {
            character.Move(-10, 0);
        }

        if(Event->key.keysym.sym == SDLK_RIGHT)
        {
            character.Move(10, 0);
        }

        if(Event->key.keysym.sym == SDLK_UP)
        {
            character.Move(0, -10);
        }

        if(Event->key.keysym.sym == SDLK_DOWN)
        {
            character.Move(0, 10);
        }

        if(Event->key.keysym.sym == SDLK_1)
        {
        }

        if(Event->key.keysym.sym == SDLK_2)
        {
        }

        if(Event->key.keysym.sym == SDLK_3)
        {
        }

        if(Event->key.keysym.sym == SDLK_4)
        {
        }


        if(Event->key.keysym.sym == SDLK_9)
        {
        }

        if(Event->key.keysym.sym == SDLK_0)
        {
        }

        if(Event->key.keysym.sym == SDLK_s)
        {

        }

        if(Event->key.keysym.sym == SDLK_RETURN)
        {
            SendMsg();
        }
    }

    if(Event->type == SDL_MOUSEBUTTONDOWN)
    {
        if(Event->button.button == SDL_BUTTON_LEFT)
        {

        }

        if(Event->button.button == SDL_BUTTON_RIGHT)
        {

        }
    }

    if(Event->type == SDL_MOUSEBUTTONUP)
    {
        if(Event->button.button == SDL_BUTTON_LEFT)
        {

        }

        if(Event->button.button == SDL_BUTTON_RIGHT)
        {

        }
    }
}
