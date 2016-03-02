#include <SDL.h>
#include "General/General.h"
#include "ServerCommunication/ServerCommunication.h"
#include "Kagan/Game.h"
#include "User/User.h"
#include "ServerCommunication/LogIn.h"

int main(int argc, char ** argv)
{
    InitEverythingGeneral();
    ServerCommunication server;

    if(server.Connect("127.0.0.1"))
    {
        LogIn logIn;
    }
    else
    {

    }

    delete(&server);
    return 0;
}
