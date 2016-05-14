#ifndef ANIMATION_H
#define ANIMATION_H

#include "Includes.h"

class Animation
{
    public:
        Animation();
        virtual ~Animation();
        bool Load(SDL_Renderer* Rend, char* FILE, int frames_, int spriteWidth, int spriteHeight);
        void NextFrame();
        void PrevFrame();

        SDL_Texture* SpriteSheet;

        int currX;
        int currY;
        int spriteWidth;
        int spriteHeight;
        int currentFrame;


    protected:
    private:

        int frames;
        int spriteSheetWidth;
        int spriteSheetHeight;

        int line_frames;



};

#endif // ANIMATION_H
