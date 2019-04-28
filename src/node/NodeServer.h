/**
 * @file NodeServer.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#ifndef NODESERVER_H
#define NODESERVER_H

#include <thread>

#include "common/Socket.h"
#include "../libs/ctpl_stl.h"
#include "Node.h"

/**
 * @brief Work description structure
 * 
 */
struct NodeWork
{
    Node* node;
    Request* req;
    json data;
};

/**
 * @brief Node server abstraction class
 * 
 */
class NodeServer
{
private:
    Socket* socket;

public:
    NodeServer(Socket* socket);
    ~NodeServer();
    void listen(Node* node, int threadPoolSize);
};

#endif // !NODESERVER_H