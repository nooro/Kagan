#include "Enemies.h"

Enemies::Enemies()
{
    //ctor
    cd = 0;
}

Enemies::~Enemies()
{
    //dtor
}

void Enemies::CreateEnemy(float hp_, float sp_, float dmg_, int range_, int as_)
{
    health = hp_;
    speed = sp_;
    dmg = dmg_;
    range = range_;
    atack_speed = as_;
}

void Enemies::Aggro(float x_, float y_, Camera* cam)
{
    float x = x_;
    float y = y_;

    if(sqrt( pow((XPos + (Width * cam->camZoom) / 2)  - x, 2)
           + pow((YPos + (Height * cam->camZoom) / 2) - y, 2) ) < range)
    {
        cout << "In range" <<endl;

        centX = XPos + (Width * cam->camZoom) / 2;
        centY = YPos + (Height * cam->camZoom) / 2;

        float xDistance = x - centX;
        float yDistance = y - centY;
        float distance = sqrt(xDistance * xDistance + yDistance * yDistance);

        speedX = x - (XPos + (Width * cam->camZoom) / 2);
        speedY = y - (YPos + (Height * cam->camZoom) / 2);

        speedX /= distance;
        speedY /= distance;

        if (distance > 1)
        {
            XPos += speedX * speed * cam->camZoom;
            YPos += speedY * speed * cam->camZoom;
        }

        Width = defaultW + YPos * 0.01;
        Height = defaultH + YPos * 0.01;
    }


}

bool Enemies::Atack(Entity target)
{
    cout << "COOL "<< cd << endl;

    if(target.XPos + target.Width < XPos) return false;
    if(target.XPos > XPos + Width) return false;
    if(target.YPos + target.Height < YPos) return false;
    if(target.YPos > YPos + Height) return false;

    return true;
}
