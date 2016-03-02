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

        SDL_Texture* SpriteSheet;

        int currX;
        int currY;
        int spriteWidth;
        int spriteHeight;


    protected:
    private:

        int frames;
        int spriteSheetWidth;
        int spriteSheetHeight;

        int line_frames;
        int currentFrame;


};

#endif // ANIMATION_H
