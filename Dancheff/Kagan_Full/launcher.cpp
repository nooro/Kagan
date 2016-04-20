#include "General/General.h"
#include "Kagan/Home.h"
#include "ServerCommunication/LogIn.h"
int main(int argc, char ** argv)
{
    InitEverythingGeneral();

    LogIn logIn;
    if(logIn.Status() == LOG_IN_SUCCESS)
        Home home;

    return 0;
}
