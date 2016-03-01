#include "ServerCommunication/ServerCommunication.h"
#include "Kagan/Game.h"
#include "User/User.h"
#include "ServerCommunication/LogIn.h"
int main(int argc, char ** argv)
{
    ServerCommunication server;
    LogIn logIn;
    if(server.Connect("127.0.0.1"))
    {

    }
    else
    {

    }

    delete(&server);
    return 0;
}
