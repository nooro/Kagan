#include "Game.h"

void Game::OnLoop()
{
    //Gets the start ticks
    OnStartup();

    //Set default cursor every frame
    SDL_SetCursor(SDL_GetDefaultCursor());

    int mX, mY;

    SDL_GetMouseState(&mX, &mY);

    int getProp = 0;

    for (list<Map>::iterator it = layer.begin(); it != layer.end(); it++)
    {
        if(it->mylayer == 0 && it->GetHoverTile(&Camera1)!= NULL)
            getProp = it->GetHoverTile(&Camera1)->tileProperty;
    }

    if(LeftButtonPressed)
    {
        Character.MoveTo_Mouse(mX, mY, getProp, &Camera1);
        Character.action = Character.WALK;
    }
    else if(RightButtonPressed)
    {
        Character.action = Character.ATACK;
        HitMark.XPos = Character.XPos;
        HitMark.YPos = Character.YPos;

        if(Character.rotation == Character.LEFT)
        {
            HitMark.XPos = Character.XPos - 60;
            HitMark.YPos = Character.YPos + 20;
        }
        if(Character.rotation == Character.RIGHT)
        {
            HitMark.XPos = Character.XPos + 120;
            HitMark.YPos = Character.YPos + 20;
        }
        if(Character.rotation == Character.DOWN_LEFT)
        {
            HitMark.XPos = Character.XPos - 40;
            HitMark.YPos = Character.YPos + 60;
        }
        if(Character.rotation == Character.DOWN_RIGHT)
        {
            HitMark.XPos = Character.XPos + 100;
            HitMark.YPos = Character.YPos + 70;
        }
        if(Character.rotation == Character.DOWN)
        {
            HitMark.XPos = Character.XPos + 20;
            HitMark.YPos = Character.YPos + 100;
        }
        if(Character.rotation == Character.UP_RIGHT)
        {
            HitMark.XPos = Character.XPos + 120;
            HitMark.YPos = Character.YPos - 20;
        }
        if(Character.rotation == Character.UP)
        {
            HitMark.XPos = Character.XPos + 40;
            HitMark.YPos = Character.YPos - 60;
        }
        if(Character.rotation == Character.UP_LEFT)
        {
            HitMark.XPos = Character.XPos - 50;
            HitMark.YPos = Character.YPos - 30;
        }
    }

    First.Aggro(Character.XPos + Character.Width / 2, Character.YPos + Character.Height / 2, &Camera1);

    system("cls");
    cout << Character.XPos << " " << Character.YPos << "      " << First.XPos << " " << First.YPos <<endl;

    First.cd++;

    if(First.Atack(Character) && First.cd >= First.atack_speed)
    {
        First.cd = 0;

        float text_x = Character.XPos + Character.Width / 2 + Camera1.camX;
        float text_y = Character.YPos + Camera1.camY;

        text_x /= WindowWidth;
        text_y /= WindowHeight;

        cout << text_x << " TEXT COORD " << text_y <<endl;

        system("cls");
        cout << "Damaging" <<endl;


        Character.takeDmg(First.dmg);
        dmgtxt.load(First.dmg, text_x, text_y);
        dmg_text.push_back(dmgtxt);
        health_bar.setCurrency(Character.hp);

    }




    //Caps the frame rate depending on the ticks that have past
    string fps = FrameRate(FPS);

    string result = "Character FPS: ";
    result.append(fps);
    const char* res = result.c_str();

    SDL_SetWindowTitle(Window, res);
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
