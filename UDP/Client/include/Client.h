#ifndef CLIENT_H
#define CLIENT_H

#include "SDL.h"
#include "SDL_net.h"
#include <SDL_image.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Client
{
    public:
        Client();
        virtual ~Client();

        void OnExecute();
        char logInfo[50];

    private:

        struct data
        {
            char user[50];
            char msg[256];
        };


        bool Running;
        SDL_Event Event;

        struct player
        {
            SDL_Rect rect;

            player()
            {
                rect.x = 0;
                rect.y = 0;
                rect.h = 32;
                rect.w = 32;
            }

            void Move(int x_, int y_)
            {
                rect.x += x_;
                rect.y += y_;
            }
        };

        player character;

        Uint32 start;
        const int FPS = 300;

        IPaddress ip;
        ///IPaddress *address;
        UDPsocket sock;
        UDPpacket *out;
        UDPpacket *in;
        UDPpacket *rec;

        string sendReturn;
        int numsent;
        int clients = 0;
        int channel;

        string IP;
        data tempData;

        SDL_Window* Window;
        SDL_Renderer* Renderer;

        ///Local
        void OnExit();
        bool OnInit();
        bool LoadContent();
        void OnEvent(SDL_Event* Event);
        void OnLoop();
        void OnRender();

        void OnStartup();
        void FrameRate(int FPS);

        static bool Draw(SDL_Renderer* Rend,
                  SDL_Texture* Temp,
                  int x, int y, int w, int h,
                  SDL_RendererFlip Flip);
        static bool Draw(SDL_Renderer* Rend,
                  SDL_Texture* Temp,
                  int x, int y, int w, int h,
                  int x2, int y2, int w2, int h2,
                  SDL_RendererFlip Flip);
        static SDL_Texture* OnLoad(SDL_Renderer* Rend, char* FILE );


        ///Server Connecting
        bool ClientReceiveStatus();
        bool ClientReceive();
        bool ConnectServer();
        bool SendMsg();
        bool ResolveHost();
        void EnterIp();
};

#endif // CLIENT_H
