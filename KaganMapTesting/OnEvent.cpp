#include "Game.h"

void Game::OnEvent(SDL_Event* Event)
{
    Character.action = Character.IDLE;
    Character.SwitchRotation(&Camera1);

    if(Event->type == SDL_QUIT)
    {
        Running = false;
    }

    if(Event->type == SDL_WINDOWEVENT)
    {
        if(Event->window.event == SDL_WINDOWEVENT_RESIZED)
        {
            MakeResponsive();
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
            if(Fullscreen == false)
            {
                Fullscreen = true;
                SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            }
            else
            {
                Fullscreen = false;
                SDL_SetWindowFullscreen(Window, SDL_WINDOW_MINIMIZED);
            }
        }

        if(Event->key.keysym.sym == SDLK_LEFT)
        {
            Camera1.onMove(10, 0);
        }

        if(Event->key.keysym.sym == SDLK_RIGHT)
        {
            Camera1.onMove(-10, 0);
        }

        if(Event->key.keysym.sym == SDLK_UP)
        {
            Camera1.onMove(0, 10);
        }

        if(Event->key.keysym.sym == SDLK_DOWN)
        {
            Camera1.onMove(0, -10);
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
            string name, path;
            name = "temp";

            path = "./Resources/Maps/";
            path.append(name);
            path.append(".map");

            ofstream clearMap;

            clearMap.open(path);

            clearMap.close();

            for (list<Map>::iterator it = layer.begin(); it != layer.end(); it++)
            {
                it->SaveMap(name);
            }
        }

        if(Event->key.keysym.sym == SDLK_n)
        {
        }

        if(Event->key.keysym.sym == SDLK_KP_PLUS)
        {
            Camera1.Zoom(true);
        }

        if(Event->key.keysym.sym == SDLK_KP_MINUS)
        {
            Camera1.Zoom(false);
        }

        if(Event->key.keysym.sym == SDLK_PAGEDOWN)
        {

        }

        if(Event->key.keysym.sym == SDLK_PAGEUP)
        {

        }
    }

    if(Event->type == SDL_MOUSEBUTTONDOWN)
    {
        if(Event->button.button == SDL_BUTTON_LEFT)
        {
            LeftButtonPressed = true;
        }

        if(Event->button.button == SDL_BUTTON_RIGHT)
        {
            RightButtonPressed = true;
        }
    }

    if(Event->type == SDL_MOUSEBUTTONUP)
    {
        if(Event->button.button == SDL_BUTTON_LEFT)
        {
            LeftButtonPressed = false;
        }

        if(Event->button.button == SDL_BUTTON_RIGHT)
        {
            RightButtonPressed = false;
        }
    }


}

