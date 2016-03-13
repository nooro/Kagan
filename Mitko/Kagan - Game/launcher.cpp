#include "Game.h"
#include "ServerConnection.h"


int main(int argc, char ** argv)
{
    ServerConnection conn;

    Game Kagan;
    Kagan.Run("Gosho");

    return 0;
}
