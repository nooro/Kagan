#include "Game.h"

bool Game::LoadContent()
{
    ///TEXTURES

    Character.Image = OnLoad(Renderer, "./Resources/Images/SIdle1.png");
    First.Image = OnLoad(Renderer, "./Resources/Images/tun.png");
    Thanks = OnLoad(Renderer, "./Resources/Images/thanks.png");
    SDL_SetTextureAlphaMod(Thanks, 140);

    if(!Idle[0].Load(Renderer, "./Resources/Images/SIdle1.png", 50, 100, 80)) return false;
    if(!Idle[1].Load(Renderer, "./Resources/Images/SIdle2.png", 50, 100, 80)) return false;
    if(!Idle[2].Load(Renderer, "./Resources/Images/SIdle3.png", 50, 100, 80)) return false;
    if(!Idle[3].Load(Renderer, "./Resources/Images/SIdle4.png", 50, 100, 80)) return false;
    if(!Idle[4].Load(Renderer, "./Resources/Images/SIdle5.png", 50, 100, 80)) return false;
    if(!Idle[5].Load(Renderer, "./Resources/Images/SIdle6.png", 50, 100, 80)) return false;
    if(!Idle[6].Load(Renderer, "./Resources/Images/SIdle7.png", 50, 100, 80)) return false;
    if(!Idle[7].Load(Renderer, "./Resources/Images/SIdle8.png", 50, 100, 80)) return false;

    if(!Walk[0].Load(Renderer, "./Resources/Images/SWalk1.png", 30, 100, 80)) return false;
    if(!Walk[1].Load(Renderer, "./Resources/Images/SWalk2.png", 30, 100, 80)) return false;
    if(!Walk[2].Load(Renderer, "./Resources/Images/SWalk3.png", 30, 100, 80)) return false;
    if(!Walk[3].Load(Renderer, "./Resources/Images/SWalk4.png", 30, 100, 80)) return false;
    if(!Walk[4].Load(Renderer, "./Resources/Images/SWalk5.png", 30, 100, 80)) return false;
    if(!Walk[5].Load(Renderer, "./Resources/Images/SWalk6.png", 30, 100, 80)) return false;
    if(!Walk[6].Load(Renderer, "./Resources/Images/SWalk7.png", 30, 100, 80)) return false;
    if(!Walk[7].Load(Renderer, "./Resources/Images/SWalk8.png", 30, 100, 80)) return false;

    if(!Atack[0].Load(Renderer, "./Resources/Images/SAtack1.png", 30, 100, 100)) return false;
    if(!Atack[1].Load(Renderer, "./Resources/Images/SAtack2.png", 30, 100, 100)) return false;
    if(!Atack[2].Load(Renderer, "./Resources/Images/SAtack3.png", 30, 100, 100)) return false;
    if(!Atack[3].Load(Renderer, "./Resources/Images/SAtack4.png", 30, 100, 100)) return false;
    if(!Atack[4].Load(Renderer, "./Resources/Images/SAtack5.png", 30, 100, 100)) return false;
    if(!Atack[5].Load(Renderer, "./Resources/Images/SAtack6.png", 30, 100, 100)) return false;
    if(!Atack[6].Load(Renderer, "./Resources/Images/SAtack7.png", 30, 100, 100)) return false;
    if(!Atack[7].Load(Renderer, "./Resources/Images/SAtack8.png", 30, 100, 100)) return false;

    if(!Spark.Load(Renderer, "./Resources/Images/Hitspark.png", 5, 96, 96)) return false;

    health_bar.init("./Resources/Images/healthbar.png", Renderer, WindowWidth, WindowHeight, 0.05, 0.05, 0.75);
    //Initialize the floating text and load its font
    dmgtxt.init("small_town.ttf", 48, White, WindowWidth, WindowHeight);
    dmgtxt.setAscend(0.01); // Sets the speed the text ascend
    dmgtxt.setFade(7); // Set the text fade speed

    if(Character.Image == NULL)
    {
        return false;
    }

    if(First.Image == NULL)
    {
        return false;
    }

    if(Thanks == NULL)
    {
        return false;
    }

    //SDL_SetTextureAlphaMod(Map1.Hover_Image, 100);

    ///MAPS



    return true;
}
