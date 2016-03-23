#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

struct Client
{
public:
    std::string username_;
    std::string password_;
    Uint32 host_;
    Uint16 port_;
    int channel_;
};

#endif // CLIENT_H_INCLUDED
