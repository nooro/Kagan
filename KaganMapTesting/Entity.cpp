#include "Game.h"

Entity::Entity()
{
    Image = NULL;

    draggable = false;
    enabled = false;
}

Entity::~Entity()
{
    //dtor
}

void Entity::CreateEntity(float x, float y, float w, float h)
{
    //Checking the image
    if(Image == NULL)
    {
        cout<<"An entity is without an Image"<<endl;
    }

    alive = true;
    hp = 100;

    //Setting coordinates
    XPos = x;
    YPos = y;
    Width = w;
    Height = h;

    defaultX = XPos;
    defaultY = YPos;
    defaultW = Width;
    defaultH = Height;

    centX = XPos + Width / 2;
    centY = YPos + Height / 2;
}

bool Entity::CheckColl(float Bx, float By, float Bw, float Bh)
{
    if ( YPos + Height < By ) return false;
    else if ( YPos > By + Bh ) return false;
    else if ( XPos + Width < Bx ) return false;
    else if ( XPos > Bx + Bw ) return false;

    return true;
}

bool Entity::CheckEntityColl(Entity object)
{
    float Bx = object.XPos;
    float By = object.YPos;
    float Bw = object.Width;
    float Bh = object.Height;

    if ( YPos + Height < By ) return false;
    else if ( YPos > By + Bh ) return false;
    else if ( XPos + Width < Bx ) return false;
    else if ( XPos > Bx + Bw ) return false;

    return true;
}

bool Entity::Hover(float Mx, float My, Camera *cam)
{
    float h = Height * cam->camZoom;
    float w = Width * cam->camZoom;


    if(Mx < XPos) return false;
    if(Mx > XPos + w) return false;
    if(My < YPos) return false;
    if(My > YPos + h) return false;

    return true;
}

void Entity::Responsive(float Kx, float Ky)
{
    XPos = defaultX * Kx;
    YPos = defaultY * Ky;
    Width = defaultW * Kx;
    Height = defaultH * Ky;
}

void Entity::MoveTo_Mouse(float x_, float y_, int prob_, Camera* cam)
{
    if(prob_ != 1)
        return;

    static float Mx = x_ - cam->camX;
    static float My = y_ - cam->camY;
    float easingAmount = 3;

    if(Mx != x_ - cam->camX)
    {
        Mx = x_ - cam->camX;
        SetPos();
    }

    if(My != y_ - cam->camY)
    {
        My = y_ - cam->camY;
        SetPos();
    }

    centX = XPos + (Width * cam->camZoom) / 2;
    centY = YPos + (Height * cam->camZoom) / 2;

    float xDistance = Mx - centX;
    float yDistance = My - centY;
    float distance = sqrt(xDistance * xDistance + yDistance * yDistance);

    speedX = Mx - (XPos + (Width * cam->camZoom) / 2);
    speedY = My - (YPos + (Height * cam->camZoom) / 2);

    speedX /= distance;
    speedY /= distance;

    if (distance > 1)
    {
        XPos += speedX * easingAmount * cam->camZoom;
        YPos += speedY * easingAmount * cam->camZoom;
    }

    Width = defaultW + YPos * 0.01;
    Height = defaultH + YPos * 0.01;
}

void Entity::DrawEntity(SDL_Renderer* Rend, Camera* cam)
{
    if(alive == false)
        return;

    Game::Draw(Rend, cam, Image, XPos, YPos, Width, Height, 0, Flip);
}

void Entity::SetPos()
{
    defaultX = XPos;
    defaultY = YPos;
}

void Entity::Animate(SDL_Renderer* Rend, Camera* cam, Animation* anim, float scale)
{
    anim->NextFrame();

    Game::Draw(Rend, cam, anim->SpriteSheet,
               XPos, YPos, Width * scale, Height * scale,
               anim->currX, anim->currY, anim->spriteWidth, anim->spriteHeight,
               0.0, SDL_FLIP_NONE);
}

void Entity::AnimateBackwards(SDL_Renderer* Rend, Camera* cam, Animation* anim, float scale)
{
    anim->PrevFrame();

    Game::Draw(Rend, cam, anim->SpriteSheet,
               XPos, YPos, Width * scale, Height * scale,
               anim->currX, anim->currY, anim->spriteWidth, anim->spriteHeight,
               0.0, SDL_FLIP_NONE);
}

void Entity::SwitchRotation(Camera* cam)
{
    int x, y;
    float cx, cy, cw, ch;

    cx = XPos;
    cy = YPos;
    cw = Width;
    ch = Height;

    SDL_GetMouseState(&x, &y);

    x = x - cam->camX;
    y = y - cam->camY;

    if(x > cx && x < cx + cw)
    {
        if(y < cy)
        {
            rotation = UP;
            return;
        }
        if(y > cy + ch)
        {
            rotation = DOWN;
            return;
        }
    }
    else if(y > cy && y < cy + ch)
    {
        if(x < cx)
        {
            rotation = LEFT;
            return;
        }
        if(x > cx + cw)
        {
            rotation = RIGHT;
            return;
        }
    }
    else if(y < cy)
    {
        if(x < cx)
        {
            rotation = UP_LEFT;
            return;
        }
        if(x > cx + cw)
        {
            rotation = UP_RIGHT;
            return;
        }
    }
    else if(y > cy + ch)
    {
        if(x < cx)
        {
            rotation = DOWN_LEFT;
            return;
        }
        if(x > cx + cw)
        {
            rotation = DOWN_RIGHT;
            return;
        }
    }

    rotation = DOWN;
    return;
}

bool Entity::takeDmg(int dmg)
{
    // if its death don't deal dmg
    if(this->alive == false)
        return false; // return that damaging was impossible

    this->hp -= dmg; // gets the dmg out of his hp

    if(this->hp <= 0) // if hp is lower than 0
    {
        this->hp = 0; // set hp to 0 so you don't overkill
        this->alive = false; // set him to death
    }

    return true; // return that damaging was fine
}
