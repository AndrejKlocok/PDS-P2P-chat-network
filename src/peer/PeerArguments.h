#ifndef PEERARGUMENTS_H
#define PEERARGUMENTS_H

#include <string>

struct PeerArguments
{
    unsigned short id;
    std::string username;
    unsigned short chatPort;
    std::string chatIpv4;
    unsigned short regPort;
    std::string regIpv4;  
};


#endif // !PEERARGUMENTS_H  