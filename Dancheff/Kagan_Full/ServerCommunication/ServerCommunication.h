#ifndef SERVERCOMMUNICATION_H_INCLUDED
#define SERVERCOMMUNICATION_H_INCLUDED

#include <SDL_net.h>
#include <iostream>
#include "PacketKeys.h"
using namespace std;

class ServerCommunication
{
public:
    ServerCommunication(char *ipAddress); //Initialize everything for the connection
    ~ServerCommunication(); //Free the used memory and close the socket

    bool Connection(); //Connect to the server. If connection is successful return true, else return false

    char LogIn(string username, string password); //Send log-in query with user-name and password to the server
    char Register(string username, string password); //Send register query with user-name and password to the server

private:
    IPaddress ip; //IP structure that holds all needed client's data for the server

    UDPsocket sock;
    UDPpacket *input;
    UDPpacket *output;
    int channel;
    int numsent;

    bool isConnected;
};


#endif // SERVERCOMMUNICATION_H_INCLUDED
