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

        int hp;
        bool alive;

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

        enum Rotation {DOWN, DOWN_LEFT, LEFT, UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT} rotation;
        enum Action {IDLE, WALK, ATACK} action;

        bool enabled;

        bool draggable;

        void CreateEntity(float x, float y, float w, float h);
        bool CheckColl(float Bx, float By, float Bw, float Bh);
        bool CheckEntityColl(Entity object);
        void Responsive(float Kx, float Ky);
        void SetPos();
        void SwitchRotation(Camera* cam);

        void MoveTo_Mouse(float x_, float y_, int prob_, Camera* cam);
        void DrawEntity(SDL_Renderer* Rend, Camera* cam);
        bool Hover(float Mx, float My, Camera* cam);
        void Animate(SDL_Renderer* Rend, Camera* cam, Animation* anim, float scale = 1);
        void AnimateBackwards(SDL_Renderer* Rend, Camera* cam, Animation* anim, float scale = 1);

        bool takeDmg(int dmg);

    private:

};

#endif // ENTITY_H
