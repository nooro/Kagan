#include "ProfileManager.h"

bool ProfileManager::FileIsExisting(string filename)
{
    ifstream tmp(filename);
    return (bool)tmp;
}

char ProfileManager::Register(string username, string password)
{
    string path = "./Database/" + username + ".data";
    if(!ProfileManager::FileIsExisting(path))
    {
        ofstream file;
        file.open(path);
        file << password;
        file.close();
        return REGISTER_SUCCESS;
    }
    return REGISTER_USED_USERNAME;
}

char ProfileManager::LogIn(string username, string password)
{
    logInPacket = "";
    string path = "./Database/" + username + ".data";
    if(ProfileManager::FileIsExisting(path))
    {
        ifstream file;
        file.open(path);
        string line;

        file >> line;
        if(line == password)
        {
            logInPacket = logInPacket + line + " ";
            file.close();
            return LOG_IN_SUCCESS;
        }
        file.close();
        return LOG_IN_INVALID_PASSWORD;
    }
    else return LOG_IN_INVALID_USERNAME;
}
