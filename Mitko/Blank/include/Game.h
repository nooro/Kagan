#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Includes.h"
#include "Entity.h"
#include "Map.h"
#include "Camera.h"
#include "Animation.h"

class Game
{
    private:

        bool Running;
        SDL_Event Event;

        SDL_Window* Window;
        SDL_Renderer* Renderer;

        SDL_Cursor* Cursor;
        SDL_Cursor* DragCursor;

        SDL_Surface* Icon;

    public:

        Game();

        //Variables for the window

        int WindowHeight;
        int WindowWidth;
        bool Fullscreen;
        float Kx;
        float Ky;

        Uint32 start;

        //Creating objects

        Map Map1;
        Map Map2;
        Map Map3;
        Camera Camera1;
        Camera UI_Cam;

        Entity Character;
        Animation Idle[16];
        int Rotation = 0;
        int SwitchRotation();

        //Graphics functions

        static bool Draw(SDL_Renderer* Rend,
                         Camera* cam,
                  SDL_Texture* Temp,
                  int x, int y, int w, int h,
                  double angle,
                  SDL_RendererFlip Flip);
        static bool Draw(SDL_Renderer* Rend,
                         Camera* cam,
                  SDL_Texture* Temp,
                  int x, int y, int w, int h,
                  int x2, int y2, int w2, int h2,
                  double angle,
                  SDL_RendererFlip Flip);
        static SDL_Texture* OnLoad(SDL_Renderer* Rend, char* FILE );

        //Other functions

        int OnExecute();

        bool OnInit();
        bool LoadContent();

        void OnEvent(SDL_Event* Event);
        void OnLoop();
        void OnRender();
        void Cleanup();
        void OnStartup();
        void FrameRate(int FPS);

        void MouseDrag(Entity *object, Camera *cam);
        //bool MouseDragReset(Entity *object);
        bool LeftButtonPressed;
        bool dragOne;

        void MakeResponsive();
};
#endif // GAME_H_INCLUDED
