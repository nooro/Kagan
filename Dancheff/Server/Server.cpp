#include "Server.h"

//Initialize everything
Server::Server()
{
    if(SDLNet_Init() < 0)
        cout << "Failed to initialize SDL_net: " << SDLNet_GetError();

    IPaddress ip;

    sock = SDLNet_UDP_Open(1234);

    input = SDLNet_AllocPacket(1024);
    output = SDLNet_AllocPacket(1024);
    ret = SDLNet_AllocPacket(1024);

    numberOfClients = 0;

    receivedData = "";
    serverIsRunning = true;

    cout << "SERVER STARTED" << endl;

    Server::MainLoop();
}

//Free the used memory and close the used socket
Server::~Server()
{
    SDLNet_FreePacket(input);
    SDLNet_FreePacket(output);
    SDLNet_FreePacket(ret);

    SDLNet_UDP_Close(sock);
    SDLNet_Quit();

    cout << "SERVER CLOSED";
}

///-----------MAIN LOOP--------------
void Server::MainLoop()
{
    while(serverIsRunning)
    {
        if (SDLNet_UDP_Recv(sock, input)) //Check if the server is receiving data from the clients
        {
            if(RECEIVED_KEY == LOG_IN_KEY)
            {
                string username = GetQueryArgument(input->data, 2);
                char logInStatus[1];
                logInStatus[0] = profile.LogIn(username, GetQueryArgument(input->data, 3));
                if(logInStatus[0] == LOG_IN_SUCCESS)
                    AddNewClient(input->address.host, input->address.port, username, input->channel);
                SendData((Uint8*)logInStatus, sizeof(logInStatus));
            }
            else if(RECEIVED_KEY == REGISTER_KEY)
            {
                char registerStatus[1];
                registerStatus[0] = profile.Register(GetQueryArgument(input->data, 2), GetQueryArgument(input->data, 3));
                SendData((Uint8*)registerStatus, sizeof(registerStatus));
                cout << "New profile registered: " << GetQueryArgument(input->data, 2) << endl;
            }
            else if(RECEIVED_KEY == KICK_KEY)
            {
                KickClient(input->address.host);
            }
            Server::SendBack();
            receivedData = "";
        }
    }
}

void Server::AddNewClient(Uint32 host, Uint16 port, string username, int channel)
{
    if(numberOfClients < MAX_CLIENTS)
    {
        clientsArray[numberOfClients].host_ = host;
        clientsArray[numberOfClients].username_ = username;
        clientsArray[numberOfClients].channel_ = channel;
        clientsArray[numberOfClients].port_ = port;
        numberOfClients++;
        cout << "New client on-line: " << username << endl;
    }
    else
    {
        Server::SendData((Uint8*)SERVER_IS_FULL_KEY, sizeof(SERVER_IS_FULL_KEY));
        cout << "The server is full" << endl;
    }
}

void Server::SendData(Uint8* data_, int length)
{
    output->address.host = input->address.host;
    output->address.port = input->address.port;
    output->channel = input->channel;
    output->data = data_;
    output->len = length;
    numsend = SDLNet_UDP_Send(sock, output->channel, output);
}

void Server::SendBack()
{
    SendData((Uint8*)true, 0);
}

void Server::ResendToAllClients(Uint32 senderHost)
{
    for(int i = 0; i < numberOfClients; i++)
    {
        if(clientsArray[i].host_ != senderHost)
        {
            ret->address.host = clientsArray[i].host_;
            ret->address.port = clientsArray[i].port_;
            ret->channel = clientsArray[i].channel_;
            ret->data = input->data;
            ret->len = input->len;
            numsend = SDLNet_UDP_Send(sock, ret->channel, ret);
        }
    }
}

string Server::GetQueryArgument(Uint8 *input, int argumentNumber)
{
    string argument = "";
    int currentArgument = 0;

    for(int i = 0; currentArgument < argumentNumber; i++)
    {
        if(input[i] == '/')
        {
            currentArgument++;
            continue;
        }

        if(currentArgument == argumentNumber - 1)
            argument += input[i];
    }
    return argument;
}

void Server::KickClient(Uint32 host)
{
    for(int i = 0; i < numberOfClients; i++)
    {
        if(clientsArray[i].host_ == host)
        {
            for(int j = i; j < numberOfClients - 1; j++)
            {
                clientsArray[j].channel_ = clientsArray[j+1].channel_;
                clientsArray[j].host_ = clientsArray[j+1].host_;
                clientsArray[j].password_ = clientsArray[j+1].password_;
                clientsArray[j].port_ = clientsArray[j+1].port_;
                clientsArray[j].username_ = clientsArray[j+1].username_;
            }
            numberOfClients--;
            cout << clientsArray[i].username_ << " gone off-line" << endl;
            break;
        }
    }
}
