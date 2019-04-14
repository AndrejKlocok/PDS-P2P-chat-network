#ifndef NODESERVER_H
#define NODESERVER_H

#include <thread>

#include "common/Socket.h"
#include "Node.h"

/**
 * @brief Node server abstraction class
 * 
 */
class NodeServer
{
private:
    Socket* socket;
    std::vector<std::thread> threads;
    
public:
    NodeServer(Socket* socket);
    ~NodeServer();
    void listen(Node* node);
    void static worker(Node* node, Request* req, json data);
};

#endif // !NODESERVER_H