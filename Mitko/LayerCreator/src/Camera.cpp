#include "Camera.h"

Camera::Camera()
{
    camZoom = 1;
    camX = 0;
    camY = 0;
    camW = 0;
    camH = 0;
}

Camera::~Camera()
{
    //dtor
}

void Camera::onMove(int x_, int y_)
{
    camX += x_;
    camY += y_;
}

void Camera::Zoom(bool io)
{
    if(io == true)
    {
        camZoom += 0.5;
        if(camZoom > 4) camZoom = 4;
    }
    else
    {
        camZoom -= 0.5;
        if(camZoom < 0.5) camZoom = 0.5;
    }
}
