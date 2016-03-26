#include "General/General.h"
#include "Kagan/Game.h"
#include "User/User.h"
#include "ServerCommunication/Register.h"

int main(int argc, char ** argv)
{
    InitEverythingGeneral();
    Register logIn;
    delete(&logIn);
    return 0;
}
