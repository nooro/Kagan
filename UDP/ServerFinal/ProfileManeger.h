#ifndef PROFILEMANEGER_H
#define PROFILEMANEGER_H

#include <iostream>
#include <fstream>
using namespace std;

class ProfileManeger
{
    public:
        bool LogIn(string username, string password);
        bool Register(string username, string password);
        string logInPacket = "";
    private:
        bool fileIsExisting(string filename);
};

#endif // PROFILEMANEGER_H
