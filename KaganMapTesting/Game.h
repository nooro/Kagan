#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Includes.h"
#include "Entity.h"
#include "Enemies.h"
#include "Camera.h"
#include "Animation.h"
#include "Map.h"
#include <list>
#include "GUIBars.h" // include bars struct
#include "DMGText.h" // include floating text struct

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
        int currentLayer;
        SDL_Texture* Thanks;
        SDL_Texture* Win;

        Uint32 start;

        Map empty_layer;
        list<Map> layer;
        Camera Camera1;

        Enemies Enemy[10];
        Entity Character;
        Entity HitMark;
        Animation Idle[8];
        Animation Walk[8];
        Animation Atack[8];
        Animation Spark;
        bool walking = false;

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
        string FrameRate(int FPS);

        void MouseDrag(Entity *object, Camera *cam);
        //bool MouseDragReset(Entity *object);
        bool LeftButtonPressed;
        bool RightButtonPressed;
        bool dragOne;

        void LoadLayer(string file);
        void LoadMap(char* map_file);
        void MakeResponsive();
        void EnemiesHandle();
        void EnemyActions(Enemies* temp);
        void Damaging(int dmg_);
        void RightClick();

        bar health_bar; // Health bar for the character
        dmgFloat dmgtxt; // single floating text to copy in to the vector
        list<dmgFloat> dmg_text; // vector of all the floating text
        SDL_Color White = {255, 255, 255, 255}; // Creates a white color from RGB and alpha
};
#endif // GAME_H_INCLUDED
