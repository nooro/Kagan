#include "ServerCommunication.h"

ServerCommunication::ServerCommunication()
{
    if(SDLNet_Init() < 0)
        cout << "Failed to initialize SDL_net: " << SDLNet_GetError() << endl;

    sock = SDLNet_UDP_Open(1234);
    output = SDLNet_AllocPacket(1024);
    input = SDLNet_AllocPacket(1024);

    channel = SDLNet_UDP_Bind(sock, -1, &ip);
    if(channel < 0)
        cout << "Failed to bind the channel: " << SDLNet_GetError() << endl;
}


ServerCommunication::~ServerCommunication()
{
    SDLNet_FreePacket(input);
    SDLNet_FreePacket(output);
    SDLNet_UDP_Close(sock);
    SDL_Quit();
    SDLNet_Quit();
}


bool ServerCommunication::Connect(char *ipAddress)
{
    //Try to connect to the server
    if(SDLNet_ResolveHost(&ip, ipAddress, 1234) < 0)
        return false; //Failed connection
    else return true; //Success connection
}

