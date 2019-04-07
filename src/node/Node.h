#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>
#include <mutex>
#include <chrono>
#include <thread>
#include <utility>

#include "common/Socket.h"

#include "NodeStorage.h"
#include "NodeFunctions.h"
#include "RpcFunctions.h"
#include "NodeArguments.h"

class NodeStorage;
class Node
{
private:
    typedef void (*rpcFunction) (Node*, json*) ;
    std::map<std::string, rpcFunction > rpcMap; 

    typedef void (*nodeFunction) (Node*, json, Request*) ;
    std::map<std::string, nodeFunction > requestMap; 
    NodeStorage* storage;
    Socket* socket;
    NodeArguments* args;
    std::mutex updateThreadMutex;
    std::map<std::pair<std::string, unsigned int>, std::thread> updateThreads;
    std::string me;
public:
    Node(NodeArguments* args);
    ~Node();
    
    NodeArguments* getArguments();
    void rpcRequest(json* request);
    void request(json data, Request* request);
    void sendSocket(json data, Request* req);
    void static nodeUpdate(Node* node, std::pair<std::string, unsigned int> ip_port);
    NodeStorage* getStorage();
    void setSocket(Socket* socket);
    void sendSocketWait(json data, Request* req);
    bool connectNode(std::string ipv4, unsigned int port, bool authority);
    void releaseThread(std::pair<std::string, unsigned int> ip_port);
    void disconnect();
    std::string getMe();
};

#endif // !NODE_H