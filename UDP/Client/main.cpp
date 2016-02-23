#include "Client.h"

using namespace std;

int main(int argc, char *argv[])
{
    Client client;

    strcpy(client.logInfo, argv[0]);
    strcat(client.logInfo, " ");
    strcat(client.logInfo, argv[1]);

    client.OnExecute();

    return 0;
}
