/**
 * @file NodeHandle.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
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
#include "common/FileOperations.h"

#include "NodeServer.h"
#include "NodeArguments.h"
#include "Node.h"

class NodeHandle
{
private:
    NodeArguments args;
    std::string pipeName;
    NodeServer* server;
    Node* node;
    
public:
    NodeHandle(/* args */);
    ~NodeHandle();
    void setRegPort(  unsigned short regPort);
    void setRegIpv4( std::string regIpv4);
    void setId( unsigned short id);

    void initNode(int argc);
    void static rpcServer(Node* node, std::string pipeName);
    void static nodeServer(Node* node, NodeServer* server, int threadsNumb);
};

#endif // !NODEHANDLE_H