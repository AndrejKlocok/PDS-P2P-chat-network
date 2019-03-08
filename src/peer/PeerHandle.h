#ifndef PEERHANDLE_H
#define PEERHANDLE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <csignal>  
#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <chrono>

#include "common/ErrHandle.h"
#include "common/UDPClient.h"

#include "PeerArguments.h"
#include "Peer.h"

class PeerHandle
{
private:
    PeerArguments args;
    std::string pipeName;
    Peer* peer;

public:
    PeerHandle(/* args */);
    ~PeerHandle();
    void setId( unsigned short id);
    void setUsername( std::string username);
    void setChatPort(  unsigned short chatPort);
    void setChatIpv4( std::string chatIpv4);
    void setRegPort(  unsigned short regPort);
    void setRegIpv4( std::string regIpv4);
    

    void processRequest(int argc);
    void static rpcServer(Peer* peer, std::string pipeName);
    void static peerServer(Peer* peer);
};

#endif // !PEERHANDLE_H