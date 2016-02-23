#include "server.h"
using namespace std;

UDPsocket sock;
UDPpacket *input;
UDPpacket *output;
UDPpacket *ret;
int numsend;

int main(int argc, char ** argv)
{
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
                    if(getClient(input->address.host) != NULL)
                    {
                        cout<<getClient(input->address.host)->username_<<": "<<input->data<<endl;
                    }

                    sendBack("true");
                    resendToAllClients(input->address.host);
                }
                else
                {
                    addNewClient(input->address.host, input->address.port, (char*)input->data, input->channel);
                }


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

void userData(string temp, int client)
{
    size_t pos = temp.find_first_of(" ");
    size_t length = temp.length() - pos;

    char username[pos];
    char password[length];

    temp.copy(password, length, pos + 1);
    temp.copy(username, pos, 0);

    clientsArray[client].username_ = username;
    clientsArray[client].password_ = password;
}

void addNewClient(Uint32 host, Uint16 port, string data, int channel)
{
    if(numberOfClients < MAX_CLIENTS)
    {
        userData(data, numberOfClients);
        clientsArray[numberOfClients].host_ = host;
        clientsArray[numberOfClients].channel_ = channel;
        clientsArray[numberOfClients].port_ = port;

        if(login(&clientsArray[numberOfClients]))
        {
            cout<< "Client logged in: " << clientsArray[numberOfClients].username_<<endl;
            sendBack("true");
            numberOfClients++;
        }
        else
        {
            sendBack("false");
            removeClient(&clientsArray[numberOfClients]);
        }


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

void sendBack(char* status_)
{
    sendData((Uint8*)status_, 8);
}

bool login (Client* client)
{
    string user = client->username_;
    string password;

    std::fstream file;

    user.append(".txt");

    file.open(user, std::fstream::in);

    if(file.fail())
    {
        printf("There is no such file\n");
        file.close();
        return false;
    }

    file >> password;

    if(password != client->password_)
    {
        printf("User inputed wrong password\n");
        file.close();
        return false;
    }

    file.close();

    return true;
}

void removeClient(Client* client)
{
    client->channel_ = 0;
    client->host_ = 0;
    client->port_ = 0;
    client->password_.clear();
    client->username_ .clear();
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
