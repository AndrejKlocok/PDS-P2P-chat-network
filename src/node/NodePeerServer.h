#ifndef NODEPEERSERVER_H
#define NODEPEERSERVER_H

#include <thread>

#include "common/Socket.h"
#include "Node.h"

class NodePeerServer
{
private:
    Socket* socket;
public:
    NodePeerServer(/* args */);
    ~NodePeerServer();
    void listen(Node* node);
    void static peerWorker(Node* node, Request* req, Socket* socket, json* data);
};

#endif // !NODEPEERSERVER_H