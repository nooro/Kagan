#ifndef SERVERCOMMUNICATION_H_INCLUDED
#define SERVERCOMMUNICATION_H_INCLUDED

#include <SDL_net.h>
#include <iostream>
#include "PacketKeys.h"
using namespace std;

class ServerCommunication
{
public:
    ServerCommunication(); //Initialize everything for the connection
    ~ServerCommunication(); //Free the used memory and close the socket

    bool Connect(char *ipAddress); //Connect to the server. If connection is successful return true, else return false

    int LogIn(char *username, char *password);

private:
    IPaddress ip; //IP structure that holds all needed client's data for the server

    UDPsocket sock;
    UDPpacket *input;
    UDPpacket *output;
    int channel;
};

#endif // SERVERCOMMUNICATION_H_INCLUDED
