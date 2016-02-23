#include "server.h"
#include "ProfileManeger.h"

UDPsocket sock;
UDPpacket *input;
UDPpacket *output;
UDPpacket *ret;
int numsend;

int main(int argc, char ** argv)
{
    ProfileManeger profile;
    profile.LogIn("Dancheff", "pass");
    cout << profile.logInPacket << endl;
    SDLNet_Init();
    IPaddress ip;


    sock = SDLNet_UDP_Open(1234);
    input = SDLNet_AllocPacket(1024);
    output = SDLNet_AllocPacket(1024);
    ret = SDLNet_AllocPacket(1024);

    cout << "SERVER STARTED" << endl;

    while (true)
    {
            if (SDLNet_UDP_Recv(sock, input))
            {
                if(clientIsOnline(input->address.host))
                {

                }
                else
                {
                    addNewClient(input->address.host, input->address.port, (char*)input->data, input->channel);
                }

                if(getClient(input->address.host) != NULL)
                {
                    cout<<getClient(input->address.host)->username_<<": "<<input->data<<endl;
                }

                sendBack();
                resendToAllClients(input->address.host);
            }



    }
    SDLNet_FreePacket(input);
    SDLNet_UDP_Close(sock);

    SDLNet_Quit();
    return 0;
}

bool clientIsOnline(Uint32 host)
{
    for(int i = 0; i < numberOfClients; ++i)
    {
        if(clientsArray[i].host_ == host)
            return true;
    }
    return false;
}

void addNewClient(Uint32 host, Uint16 port, string username, int channel)
{
    if(numberOfClients < MAX_CLIENTS)
    {
        clientsArray[numberOfClients].host_ = host;
        clientsArray[numberOfClients].username_ = username;
        clientsArray[numberOfClients].channel_ = channel;
        clientsArray[numberOfClients].port_ = port;
        numberOfClients++;
    }
    else
    {
        sendData((Uint8*)"The server is full", sizeof("The server is full"));
    }
}

void resendToAllClients(Uint32 senderHost)
{
    for(int i = 0; i < numberOfClients; i++)
    {
        if(clientsArray[i].host_ != senderHost)
        {
            ret->address.host = clientsArray[i].host_;
            ret->address.port = clientsArray[i].port_;
            ret->channel  = clientsArray[i].channel_;
            ret->data = input->data;
            ret->len = input->len;
            numsend = SDLNet_UDP_Send(sock, ret->channel, ret);
            if(!numsend)
            {
                printf("SDLNet_UDP_Send failed %s", SDLNet_GetError());
                exit(1);
            }
        }
    }
}

void sendData(Uint8* data_, int length)
{
    output->address = input->address;
    output->channel = input->channel;
    output->data = data_;
    output->len = length;
    numsend = SDLNet_UDP_Send(sock, output->channel, output);
}

void sendBack()
{
    sendData((Uint8*)true, 0);
}

Client *getClient(Uint32 host)
{
    for(int i = 0; i < numberOfClients; i++)
    {
        if(clientsArray[i].host_ == host)
            return &clientsArray[i];
    }
    return NULL;
}
