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

typedef void (*baseFunction) (Node*, json, Request*);
typedef void (*rpcFunction) (Node*, json*);

/**
 * @brief Node abstraction class
 * 
 */
class Node
{
private:
    std::map<std::string, rpcFunction > rpcMap; 
    std::map<std::string, baseFunction > requestMap; 
    NodeStorage* storage;
    Socket* socket;
    NodeArguments* args;
    std::thread updateThread;
    std::string me;
public:
    Node(NodeArguments* args);
    ~Node();

    void registerRpcRequest(std::string keyName, rpcFunction func);
    void registerBaseRequest(std::string keyName, baseFunction func);
    NodeArguments* getArguments();
    void rpcRequest(json* request);
    void request(json data, Request* request);
    void sendSocket(json data, Request* req);
    void static nodeUpdate(Node* node);
    void static nodeDisconnect(Node* node, std::pair<std::string, unsigned int> ip_port, Request* request);
    NodeStorage* getStorage();
    void setSocket(Socket* socket);
    void sendSocketWait(json data, Request* req);
    bool connectNode(std::string ipv4, unsigned int port, bool authority);
    void releaseThread(std::pair<std::string, unsigned int> ip_port);
    void disconnect();
    std::string getMe();
};

#endif // !NODE_H