#ifndef PEER_H
#define PEER_H

#include <map>
#include <string>
#include <thread>
#include <mutex>

#include "../libs/json.hpp"
#include "common/ErrHandle.h"
#include "common/MyExceptions.h"
#include "common/Socket.h"

#include "PeerFunctions.h"
#include "RpcFunctions.h"
#include "PeerArguments.h"

class Peer
{
private:
    typedef void (*argFunction) (Peer*, json*) ;
    std::map<std::string, argFunction > rpcMap; 

    typedef void (*nodeFunction) (Peer*, json, Request*, Socket*) ;
    std::map<std::string, nodeFunction > requestMap; 

    PeerArguments* peerArguments;
    Socket* socket;
    Request* requestAddr;
    std::thread peerConnectionThread;
    bool isExc;

    std::mutex regUsrsMutex, ackMutex;
    unsigned short transactionNumber;
    std::vector<unsigned short> acknowledgements;

public:
    Peer(PeerArguments* args, Socket* socket);
    ~Peer();
    void static peerCommunicator(PeerArguments* args, Peer* peer);
    void disconnectFromNode();
    void sendSocket(json data);
    
    void setExc();
    bool getIsExc();
    void rpcRequest(json request);
    void request(json data, Request* request, Socket* socket);
    unsigned short getTransactionNumber();
    bool acknowledge(unsigned short txid);
    void insertAck(unsigned short txid);

};

#endif // !PEER_H