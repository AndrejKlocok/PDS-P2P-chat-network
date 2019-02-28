#ifndef NODERPCSERVER_H
#define NODERPCSERVER_H

#include <thread>

#include "common/Socket.h"
#include "Node.h"


class NodeRPCServer
{
private:
    Socket* socket;
public:
    NodeRPCServer(ushort port);
    ~NodeRPCServer();
    void listen(Node* node);
    void static rpcWorker(Node* node, Request* req, Socket* socket, json* data);
};


#endif // !NODERPCSERVER_H