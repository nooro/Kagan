#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <SDL_net.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <stdio.h>


const int MAX_CLIENTS = 10;

struct Client
{
public:
    std::string username_;
    Uint32 host_;
    Uint16 port_;
    int channel_;
};

Client clientsArray[MAX_CLIENTS];

int numberOfClients = 0;

bool clientIsOnline(Uint32 host);
void addNewClient(Uint32 host, Uint16 port, std::string username, int channel);
void sendBack();
void resendToAllClients(Uint32 senderHost);
void sendData(Uint8* data_, int length);

Client *getClient(Uint32 host);
#endif // SERVER_H_INCLUDED
