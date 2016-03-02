#include "Game.h"
#include "Animation.h"

Animation::Animation()
{
    SpriteSheet = NULL;
    frames = 0;
    spriteSheetWidth = 0;
    spriteSheetHeight = 0;
    spriteWidth = 0;
    spriteHeight = 0;
    line_frames = 0;
    currentFrame = 0;
    currX = 0;
    currY = 0;
}

Animation::~Animation()
{
    //dtor
}

bool Animation::Load(SDL_Renderer* Rend, char* FILE, int frames_, int spriteWidth_, int spriteHeight_)
{
    //Loads the sprite sheet image
    SpriteSheet = Game::OnLoad(Rend, FILE);
    if(SpriteSheet == NULL) return false;

    //Gets the SpriteSheetWidth and SpriteSheetHeight
    SDL_QueryTexture(SpriteSheet, NULL, NULL, &spriteSheetWidth, &spriteSheetHeight);

    //Sets parameters
    frames = frames_;
    spriteWidth = spriteWidth_;
    spriteHeight = spriteHeight_;

    line_frames = spriteSheetWidth/spriteWidth;

    return true;
}

void Animation::NextFrame()
{
    //Calculating the width and hight of a frame in a sprite sheet
    currX = (currentFrame % line_frames) * spriteWidth;
    currY = (currentFrame / line_frames) * spriteHeight;

    //Going to next frame
    currentFrame++;

    if(currentFrame == frames)
    {
        currentFrame = 0;
    }
}
