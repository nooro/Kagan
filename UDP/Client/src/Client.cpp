#include "Client.h"

Client::Client()
{
    Running = true;
}

Client::~Client()
{
    //dtor
}

void Client::OnExecute()
{
    if(OnInit() == false)
    {
        printf("Init Failed\n");
        Running = false;
    }

    if(ResolveHost() == false && Running == true)
    {
        printf("ResolveHost failed\n");
        Running = false;
    }

    while(Running)
    {

        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();

    }

    OnExit();
}

bool Client::ResolveHost()
{
    EnterIp();

    if(SDLNet_ResolveHost(&ip, IP.c_str(), 1234) == -1)
    {
        printf("SDLNet_ResolveHost - &s\n", SDLNet_GetError());
        return false;
    }

    sock = SDLNet_UDP_Open(0);
    out = SDLNet_AllocPacket(1024);
    in = SDLNet_AllocPacket(1024);
    rec = SDLNet_AllocPacket(1024);

    channel = SDLNet_UDP_Bind(sock, -1, &ip);

    if(channel  == -1)
    {
        printf("SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
        return false;
    }

    ///ADDRESS
    /*address = SDLNet_UDP_GetPeerAddress(sock, channel);

    if(!address)
    {
        printf("SDLNet_UDP_GetPeerAddress: %s\n", SDLNet_GetError());
        return false;
    }
    else
    {

    }*/

    printf("CLIENT STARTED\n"); fflush(stdout);

    if(ConnectServer() == false)
    {
        return false;
    }

    return true;
}

bool Client::SendMsg()
{
    cout << "Write a msg : ";
    cin.getline(tempData.msg, 255);
    sendReturn = false;

    out->data = (Uint8*)&tempData.msg;
    out->len = sizeof(tempData.msg);

    numsent = SDLNet_UDP_Send(sock, 0, out);

    if(ClientReceiveStatus() == false)
    {
        printf("SDLNet_ClientReceive failed\n");
        return false;
    }

    if(!numsent)
    {
        printf("SDLNet_UDP_Send - %s\n", SDLNet_GetError());
        return false;
    }

    return true;
}


void Client::EnterIp()
{
    cout << "Enter IP (xxx.xxx.xxx.xxx): ";
    cin >> IP; getchar();

    if(IP == "null")
    {
        IP = "127.0.0.1";
    }

    if(IP == "hotspot")
    {
        IP = "192.168.43.134";
    }

    cout << "Connecting to ip : " << IP <<endl;
}

bool Client::ConnectServer()
{
    strcpy(tempData.user, "Mitko");

    cout<<tempData.user<<endl;

    out->data = (Uint8*)&tempData.user;
    out->len = sizeof(tempData.user);

    SDLNet_UDP_Send(sock, 0, out);

    cout<<"Connecting please wait ..."<<endl;

    if(ClientReceiveStatus() == false)
    {
        return false;
    }

    system("cls");

    return true;
}

bool Client::ClientReceiveStatus()
{
    Uint32 connecting = SDL_GetTicks();

    while(true)
    {
        if(SDLNet_UDP_Recv(sock, in))
        {
            sendReturn = (bool)in->data;
            if(sendReturn == true)
                return true;
            else
            {
                cout<<"Recv: "<<(char*)in->data<<endl;
                Sleep(1000);
                return false;
            }
        }

        if(5000 < SDL_GetTicks() - connecting)
        {
            cout << "Connection failed" <<endl;
            return false;
        }
    }
}

bool Client::ClientReceive()
{
    if(SDLNet_UDP_Recv(sock, rec))
    {
        cout<<rec->data<<endl;
    }
}

void Client::OnExit()
{
    printf("CLIENT STOPPED\n"); fflush(stdout);
    SDLNet_FreePacket(out);
    SDLNet_FreePacket(in);
    SDLNet_UDP_Close(sock);
    SDLNet_Quit();

    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
}
