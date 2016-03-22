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

    if( YPos + h < My) return false;
    else if( YPos > My) return false;
    else if( XPos + w < Mx) return false;
    else if( XPos > Mx) return false;

    return true;
}

void Entity::Responsive(float Kx, float Ky)
{
    XPos = defaultX * Kx;
    YPos = defaultY * Ky;
    Width = defaultW * Kx;
    Height = defaultH * Ky;
}

void Entity::MoveTo_Mouse(float x_, float y_, Camera* cam)
{
    static float Mx = x_ - cam->camX;
    static float My = y_ - cam->camY;
    float easingAmount = 2;

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
        XPos += speedX * easingAmount;
        YPos += speedY * easingAmount;
    }
}

void Entity::DrawEntity(SDL_Renderer* Rend, Camera* cam)
{
    Game::Draw(Rend, cam, Image, XPos, YPos, Width, Height, 0, Flip);
}

void Entity::SetPos()
{
    defaultX = XPos;
    defaultY = YPos;
}
