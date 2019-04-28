/**
 * @file PeerArguments.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#ifndef PEERARGUMENTS_H
#define PEERARGUMENTS_H

#include <string>

/**
 * @brief Arguments of peer deamon
 * 
 */
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