/**
 * @file Peer.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#ifndef PEER_H
#define PEER_H

#include <map>
#include <string>
#include <thread>

#include "../common/ErrHandle.h"
#include "../common/MyExceptions.h"
#include "../common/Socket.h"

#include "PeerStorage.h"
#include "PeerFunctions.h"
#include "RpcFunctions.h"
#include "PeerArguments.h"

class PeerStorage;

typedef void (*rpcFunction) (Peer*, json*) ;
typedef void (*baseFunction) (Peer*, json, Request*) ;

/**
 * @brief Peer class
 * 
 */
class Peer
{
private:
    std::map<std::string, rpcFunction > rpcMap; 
    std::map<std::string, baseFunction > requestMap; 
    PeerArguments* peerArguments;
    Socket* socket;
    Request* requestAddr;
    std::thread peerConnectionThread;
    PeerStorage* storage;

public:
    Peer(PeerArguments* args);
    ~Peer();
    void registerRpcRequest(std::string keyName, rpcFunction func);
    void registerBaseRequest(std::string keyName, baseFunction func);
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