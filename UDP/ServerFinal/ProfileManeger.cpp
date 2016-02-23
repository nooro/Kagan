#include "ProfileManeger.h"

bool ProfileManeger::fileIsExisting(string filename)
{
    ifstream tmp(filename);
    return (bool)tmp;
}

bool ProfileManeger::Register(string username, string password)
{
    string path = "./Database/" + username + ".data";
    if(!ProfileManeger::fileIsExisting(path))
    {
        ofstream file;
        file.open(path);
        file << password << "\n";
        file.close();
        return true;
    }
    return false;
}

bool ProfileManeger::LogIn(string username, string password)
{
    logInPacket = "";
    string path = "./Database/" + username + ".data";
    if(ProfileManeger::fileIsExisting(path))
    {
        ifstream file;
        file.open(path);
        string line;

        file >> line;
        if(line == password)
        {
            logInPacket = logInPacket + line + " ";
            cout << "Log-in: " << username << endl;
            file.close();
            return true;
        }
        file.close();
        return false;
    }
    else return false;
}
