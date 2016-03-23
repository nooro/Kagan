#ifndef PROFILEMANEGER_H
#define PROFILEMANEGER_H

#include <iostream>
#include <fstream>
#include "PacketKeys.h"
using namespace std;

class ProfileManager
{
public:
    char LogIn(string username, string password);
    char Register(string username, string password);
    string logInPacket = "";

private:
    void SplitTheInputPacket(string input);
    bool FileIsExisting(string filename);
};

#endif // PROFILEMANEGER_H
