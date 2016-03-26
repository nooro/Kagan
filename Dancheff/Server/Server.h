#ifndef SERVER_H
#define SERVER_H

#include <SDL_net.h>
#include <iostream>
#include "Client.h"
#include "PacketKeys.h"
#include "ProfileManager.h"
using namespace std;

class Server
{
public:
    Server();
    ~Server();

private:
    ProfileManager profile;
    bool serverIsRunning;

    int numberOfClients;                //Number of all on-line clients at the moment
    static const int MAX_CLIENTS = 10;  //The max number of clients is 10 for better performance
    Client clientsArray[MAX_CLIENTS];   //Array of all on-line clients

    UDPsocket sock;
    UDPpacket *input;  //Packet that the server is receiving from the clients
    UDPpacket *output; //Packet that the server is sending to the clients
    UDPpacket *ret;    //Packet that the server is resending to the clients

    int numsend;

    char *receivedData; // The data that the server receives from the clients
    #define RECEIVED_KEY input->data[0]

    void MainLoop(); //Endless loop in witch the server is receiving, process and send data
    void SendBack(); //When client sends data the server returns to it 'true' to indicate that the data is successfully received
    Client *getClient(Uint32 host); //Search client it's host from the clients array and returns it
    void SendData(Uint8* data_, int length); //Send data to clients the server
    void ResendToAllClients(Uint32 senderHost); //When one client sends data the server resends it to all other clients (the magic of synchronization)
    void AddNewClient(Uint32 host, Uint16 port, string username, int channel); //Add new client to the clients' array
    string GetQueryArgument(Uint8 *input, int argumentNumber); //Get argument from the query

};

#endif // SERVER_H
