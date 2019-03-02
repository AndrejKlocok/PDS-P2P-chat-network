#ifndef NODESERVER_H
#define NODESERVER_H

#include <thread>

#include "common/Socket.h"
#include "Node.h"

class NodeServer
{
private:
    Socket* socket;
public:
    NodeServer(std::string IP, unsigned short port);
    ~NodeServer();
    void listen(Node* node);
    void static peerWorker(Node* node, Request* req, Socket* socket, json* data);
};

#endif // !NODESERVER_H