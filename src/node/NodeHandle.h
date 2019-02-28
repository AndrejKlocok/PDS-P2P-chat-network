#ifndef NODEHANDLE_H
#define NODEHANDLE_H

#include <string>
#include <map>
#include <thread>

#include "common/ErrHandle.h"
#include "common/UDPClient.h"

#include "NodeArguments.h"
#include "NodeRPCServer.h"
#include "Node.h"

class NodeHandle
{
private:
    NodeArguments args;
public:
    NodeHandle(/* args */);
    ~NodeHandle();
    void setRegPort(  unsigned short regPort);
    void setRegIpv4( std::string regIpv4);
    void setId( unsigned short id);

    void processRequest(int argc);
    void static rpcServer(Node* node);
    void static peerServer(Node* node);
    void static nodeServer(Node* node);
};

#endif // !NODEHANDLE_H