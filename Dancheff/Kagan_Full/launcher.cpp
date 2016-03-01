#include "ServerCommunication/ServerCommunication.h"
#include "Kagan/Game.h"
#include "User/User.h"

int main(int argc, char ** argv)
{
    ServerCommunication server;
    Game Kagan;
    User user;

    if(server.Connect("127.0.0.1"))
    {

    }
    else
    {

    }

    delete(&user);
    delete(&Kagan);
    delete(&server);

    return 0;
}
