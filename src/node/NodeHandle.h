#ifndef NODEHANDLE_H
#define NODEHANDLE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <csignal>  
#include <iostream>
#include <string>
#include <map>
#include <thread>

#include "common/ErrHandle.h"
#include "common/UDPClient.h"

#include "NodeArguments.h"
#include "Node.h"

class NodeHandle
{
private:
    NodeArguments args;
    std::string pipeName;
public:
    NodeHandle(/* args */);
    ~NodeHandle();
    void setRegPort(  unsigned short regPort);
    void setRegIpv4( std::string regIpv4);
    void setId( unsigned short id);

    void processRequest(int argc);
    void static rpcServer(Node* node, std::string pipeName);
    void static nodeServer(Node* node);
};

#endif // !NODEHANDLE_H