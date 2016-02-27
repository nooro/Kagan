#include "Game.h"

void Game::OnEvent(SDL_Event* Event)
{
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
            ofstream clearMap;

            clearMap.open("./Resources/Maps/temp.map");

            clearMap.close();

            for (list<Map>::iterator it = layer.begin(); it != layer.end(); it++)
            {
                it->SaveMap();
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
            empty_layer.page --;
            if(empty_layer.page < 0) empty_layer.page = 0;
        }

        if(Event->key.keysym.sym == SDLK_PAGEUP)
        {
            empty_layer.page ++;
            if(empty_layer.page > 7) empty_layer.page = 7;
        }

        if(Event->key.keysym.sym == SDLK_DELETE)
        {
            for (list<Map>::iterator it = layer.begin(); it != layer.end(); it++)
            {
                if(currentLayer == it->mylayer)
                {
                    Map::hoverTile = it->GetHoverTile(&Camera1);
                    if(it->hoverTile != NULL)
                    {
                        it->DeleteTile();
                    }
                }
            }
        }

        if(Event->key.keysym.sym ==  SDLK_p)
        {
            layer.push_back(empty_layer);
            Map::layer ++;
        }

        if(Event->key.keysym.sym == SDLK_o)
        {
            if(Map::layer > 0)
            {
                layer.pop_back();
                Map::layer --;
            }
        }

        if(Event->key.keysym.sym == SDLK_k)
        {
            if(currentLayer > 0)
                currentLayer --;
        }

        if(Event->key.keysym.sym == SDLK_l)
        {
            if(currentLayer < Map::layer - 1)
                currentLayer ++;
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

        }
    }


}
