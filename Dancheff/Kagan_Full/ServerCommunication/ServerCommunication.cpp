#include "ServerCommunication.h"

ServerCommunication::ServerCommunication(char *ipAddress)
{
    //Initialize SDL_NET
    if(SDLNet_Init() < 0)
        cout << "Failed to initialize SDL_net: " << SDLNet_GetError() << endl;


    //Try to connect to the server
    if(SDLNet_ResolveHost(&ip, ipAddress, 1234) < 0)
        isConnected = false; //Failed connection
    else
        isConnected = true; //Success connection


    //Open new UDP socket for server-client communication
    sock = SDLNet_UDP_Open(0);
    if(sock == NULL)
        cout << "Failed to open UDP socket: " << SDLNet_GetError() << endl;

    //Packet for the data that the client send to the server
    output = SDLNet_AllocPacket(1024);

    //Packet for the received data
    input = SDLNet_AllocPacket(1024);

    channel = SDLNet_UDP_Bind(sock, -1, &ip);
    if(channel == -1)
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


bool ServerCommunication::Connection() { return isConnected; }

char ServerCommunication::LogIn(string username, string password)
{
    char query[50];
    int cursor = 0; //Shows which is the last element changed

    //Put the query key in the front of the query
    query[cursor] = LOG_IN_KEY;
    cursor++;

    //Put separator between the user-name and the password
    query[cursor] = '/';
    cursor++;

    //Put the user-name in the query
    for(int i = 0; username[i] != NULL; i++, cursor++)
        query[cursor] = username[i];

    //Put separator between the user-name and the password
    query[cursor] = '/';
    cursor++;

    //Put the password in the query
    for(int i = 0; password[i] != NULL; i++, cursor++)
    {
        query[cursor] = password[i];
    }

    //Send the complete packet like query like '1/user-name/password'
    output->data = (Uint8*)query;
    output->len = sizeof(query);
    numsent = SDLNet_UDP_Send(sock, channel, output);

    //Receive the result from the log-in
    while(true)
    {
        if (SDLNet_UDP_Recv(sock, input))
            return (char)input->data[0];
    }
}

char ServerCommunication::Register(string username, string password)
{
    char query[50];
    int cursor = 0; //Shows which is the last element changed

    //Put the query key in the front of the query
    query[cursor] = REGISTER_KEY;
    cursor++;

    //Put separator between the user-name and the password
    query[cursor] = '/';
    cursor++;

    //Put the user-name in the query
    for(int i = 0; username[i] != NULL; i++, cursor++)
        query[cursor] = username[i];

    //Put separator between the user-name and the password
    query[cursor] = '/';
    cursor++;

    //Put the password in the query
    for(int i = 0; password[i] != NULL; i++, cursor++)
    {
        query[cursor] = password[i];
    }

    //Send the complete packet like query like '2/user-name/password'
    output->data = (Uint8*)query;
    output->len = sizeof(query);
    numsent = SDLNet_UDP_Send(sock, channel, output);

    //Receive the result from the log-in
    while(true)
    {
        if (SDLNet_UDP_Recv(sock, input))
            return (char)input->data[0];
    }
}
