#ifndef ONANIMATE_H
#define ONANIMATE_H

#include "Includes.h"

class OnAnimate
{
    public:
        OnAnimate();
        void Animation();
        SDL_Texture* Animate;

        int Frames;
        int Width;
        int Height;
        int SpriteWidth;
        int SpriteHeight;

        int height;
        int width;
        int frame;
        int MaxFrame;
        int FirstX;
        int FirstY;
};

#endif // ONANIMATE_H
