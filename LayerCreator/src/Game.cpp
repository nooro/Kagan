#include "Game.h"

Game::Game()
{
    //ctr

    Window = NULL;

    Icon = NULL;
    Running = true;
    LeftButtonPressed = false;
    dragOne = false;
    Fullscreen = false;
    Kx = 0;
    Ky = 0;

    currentLayer = 0;
    Camera1.camX = 240;
}

int Game::OnExecute()
{
    cout<<"Execute"<<endl;

    if(OnInit() == false)
    {
        Sleep(1000);
        return -1;
    }

    cout<<"Init = true"<<endl;

    while(Running)
    {
    cout<<"Running = true\n"<<endl;

        while(SDL_PollEvent(&Event))
        {
            cout<<"Event = true"<<endl;
            OnEvent(&Event);
        }

        cout<<"\nLoop phase start"<<endl;
        OnLoop();
        cout<<"Loop phase end\n"<<endl;

        cout<<"\nRender phase start"<<endl;
        OnRender();
        cout<<"Render phase End\n"<<endl;

        system("cls");
    }

    cout<<"Cleaning started"<<endl;
    Cleanup();
    cout<<"Cleaning ended"<<endl;

    return 0;
}

int main(int argc, char* argv[])
{
    Game theGame;

    return theGame.OnExecute();
}
