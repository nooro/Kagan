#include "OnAnimate.h"

OnAnimate::OnAnimate()
{
    width = 0;
    height = 0;
    frame = 0;
    FirstX = 0;
    FirstY = 0;
    Animate = NULL;
}

void OnAnimate::Animation()
{
    //Calculating max frame
    MaxFrame = SpriteWidth/Width;

    //Calculating the width and hight of a frame in a sprite sheet
    width = (FirstX + frame % MaxFrame) * Width;
    height = (FirstY + frame / MaxFrame) * Height;

    //Going to next frame
    frame++;

    if(frame == Frames)
    {
        frame = 0;
    }
}
