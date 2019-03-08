#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>
#include <mutex>
#include <chrono>
#include <thread>

#include "common/Socket.h"

#include "NodeFunctions.h"
#include "RpcFunctions.h"

using json = nlohmann::json;

struct PeerRecord
{
    std::string username;
    std::string ip;
    unsigned short port;
    unsigned int timeout;
};


class Node
{
private:
    std::map<std::string, PeerRecord*> users_registerd;
    std::map<std::string, PeerRecord*> users_abroad;
    
    typedef void (*rpcFunction) (Node*, json*, json*) ;
    std::map<std::string, rpcFunction > rpcMap; 

    typedef void (*nodeFunction) (Node*, json, Request*, Socket*) ;
    std::map<std::string, nodeFunction > requestMap; 
    
    std::vector<unsigned short> acknowledgements;

    std::mutex regUsrsMutex, ackMutex;
    bool isExc;
    unsigned short transactionNumber;
public:
    Node();
    ~Node();
    std::vector<PeerRecord*> getUsersVec();
    void setExc();
    bool getIsExc();
    void rpcRequest(json* request, json* response);
    void request(json data, Request* request, Socket* socket);
    bool addNewLocalPeer(PeerRecord* record);
    bool incPeerTimer(std::string username, int time);
    unsigned short getTransactionNumber();
    bool acknowledge(unsigned short txid);
    void insertAck(unsigned short txid);
};

#endif // !NODE_H