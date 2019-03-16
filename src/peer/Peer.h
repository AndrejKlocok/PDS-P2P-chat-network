#ifndef PEER_H
#define PEER_H

#include <map>
#include <string>
#include <thread>
#include <mutex>
#include <deque>

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

    typedef void (*nodeFunction) (Peer*, json, Request*) ;
    std::map<std::string, nodeFunction > requestMap; 

    PeerArguments* peerArguments;
    Socket* socket;
    Request* requestAddr;
    std::thread peerConnectionThread;
    bool isExc, isHello;
    bool peersDisp;
    std::deque<json> messages;
    std::mutex msgMutex, ackMutex;
    unsigned short transactionNumber;
    std::vector<unsigned short> acknowledgements;

public:
    Peer(PeerArguments* args, Socket* socket);
    ~Peer();
    void static peerCommunicator(PeerArguments* args, Peer* peer);
    void disconnectFromNode();
    void sendSocket(json data);
    void sendSocket(json data, Request* req);
    void rpcRequest(json request);
    void request(json data, Request* request);
    void reconect(std::string ipv4, unsigned short port);

    void insertMessage(json message);
    json getFrontMessage();
    void sendMessages(json peers);
    unsigned short getTransactionNumber();
    bool acknowledge(unsigned short txid);
    void insertAck(unsigned short txid);
    void waitAck(int ackNumber);
    bool getIsExc();
    void setExc();
    bool getHello();
    void setHello(bool value);
    bool getPeerDist();
    void setPeerDisp(bool value);
};

#endif // !PEER_H