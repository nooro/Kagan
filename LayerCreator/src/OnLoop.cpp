#include "Game.h"

void Game::OnLoop()
{
    //Gets the start ticks
    OnStartup();

    //Set default cursor every frame
    SDL_SetCursor(SDL_GetDefaultCursor());

    int mX, mY;

    SDL_GetMouseState(&mX, &mY);


    if(LeftButtonPressed)
    {
        empty_layer.ChangeTile();
        for (list<Map>::iterator it = layer.begin(); it != layer.end(); it++)
        {
            if(currentLayer == it->mylayer)
            {
                Map::hoverTile = it->GetHoverTile(&Camera1);
                if(it->hoverTile != NULL)
                {
                    it->PlaceTile();
                }
            }
        }
    }



    //Caps the frame rate depending on the ticks that have past
    FrameRate(FPS);
}

void Game::MouseDrag(Entity *object, Camera *cam)
{
    //Cursor on Hover

    if(dragOne == true && object->draggable == false)
        return;

    int mouseX = 0;
    int mouseY = 0;

    SDL_GetMouseState(&mouseX, &mouseY);

    mouseX -= cam->camX;
    mouseY -= cam->camY;

    if(object->Hover(mouseX, mouseY, cam) == true)
    {
        SDL_SetCursor(Cursor);

        if(LeftButtonPressed == true)
            object->draggable = true;
    }

    if(LeftButtonPressed == false)
        object->draggable = false;

    if(object->draggable == true)
    {
        object->XPos = mouseX - (object->Width * cam->camZoom) / 2;
        object->YPos = mouseY - (object->Height * cam->camZoom) / 2;
        SDL_SetCursor(DragCursor);
        dragOne = true;
    }
    else
        dragOne = false;
}

void Game::MakeResponsive()
{
    SDL_GetWindowSize(Window, &WindowWidth, &WindowHeight);

    float Window_Width = WindowWidth;
    float Window_Height = WindowHeight;

    Kx = Window_Width / MIN_WINDOW_X;
    Ky = Window_Height / MIN_WINDOW_Y;
}
