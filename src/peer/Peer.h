#ifndef PEER_H
#define PEER_H

#include <map>
#include <string>
#include <thread>

#include "common/ErrHandle.h"
#include "common/MyExceptions.h"
#include "common/Socket.h"

#include "PeerStorage.h"
#include "PeerFunctions.h"
#include "RpcFunctions.h"
#include "PeerArguments.h"

class PeerStorage;

class Peer
{
private:
    typedef void (*argFunction) (Peer*, json*) ;
    std::map<std::string, argFunction > rpcMap; 

    typedef void (*nodeFunction) (Peer*, json, Request*) ;
    std::map<std::string, nodeFunction > requestMap; 

    PeerArguments* peerArguments;
    Socket* socket;
    Request* requestAddr;
    std::thread peerConnectionThread;
    PeerStorage* storage;

public:
    Peer(PeerArguments* args);
    ~Peer();
    void static peerCommunicator(PeerArguments* args, Peer* peer);
    void setSocket(Socket* socket);
    void disconnectFromNode();
    void sendSocket(json data);
    void sendSocket(json data, Request* req);
    void sendSocketWait(json data);
    void sendSocketWait(json data, Request* req);
    void rpcRequest(json request);
    void request(json data, Request* request);
    void reconect(std::string ipv4, unsigned short port);
    void runCommunicator();
    PeerStorage* getStorage();
};

#endif // !PEER_H