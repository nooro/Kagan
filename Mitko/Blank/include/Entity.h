#ifndef ENTITY_H
#define ENTITY_H

#include "Includes.h"
#include "Camera.h"
#include "Animation.h"

class Entity
{
    public:
        Entity();
        ~Entity();

        SDL_Texture* Image;
        SDL_RendererFlip Flip;

        float XPos;
        float YPos;
        float Width;
        float Height;

        float defaultX;
        float defaultY;
        float defaultW;
        float defaultH;

        float centX;
        float centY;
        float speedX;
        float speedY;

        bool enabled;

        bool draggable;

        void CreateEntity(float x, float y, float w, float h);
        bool CheckColl(float Bx, float By, float Bw, float Bh);
        bool CheckEntityColl(Entity object);
        void Responsive(float Kx, float Ky);
        void SetPos();

        void MoveTo_Mouse(float x_, float y_, Camera* cam);
        void DrawEntity(SDL_Renderer* Rend, Camera* cam);
        bool Hover(float Mx, float My, Camera* cam);
        void Animate(SDL_Renderer* Rend, Camera* cam, Animation* anim);

    private:

};

#endif // ENTITY_H
