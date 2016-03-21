#ifndef CAMERA_H
#define CAMERA_H

#include "Includes.h"

class Camera
{
    public:
        Camera();
        virtual ~Camera();

        void onMove(int x_, int y_);
        void Zoom(bool io);

        int camX;
        int camY;
        int camW;
        int camH;
        double camZoom;
    protected:
    private:






};

#endif // CAMERA_H
