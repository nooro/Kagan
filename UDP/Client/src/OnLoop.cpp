#include "Client.h"

void Client::OnLoop()
{
    //Gets the start ticks
    OnStartup();

    ClientReceive();

    //Caps the frame rate depending on the ticks that have past
    FrameRate(FPS);
}
