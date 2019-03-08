#ifndef PEER_H
#define PEER_H

#include <map>
#include <string>
#include <thread>

#include "../libs/json.hpp"
#include "common/ErrHandle.h"
#include "common/MyExceptions.h"
#include "common/Socket.h"

#include "PeerFunctions.h"
#include "PeerArguments.h"
using json = nlohmann::json;

class Peer
{
private:
    int transactionNumber;
    typedef void (*argFunction) (Peer*, json*) ;
    std::map<std::string, argFunction > peerFunctions; 
    PeerArguments* peerArguments;
    Socket* socket;
    std::thread peerConnectionThread;
    bool isExc;
public:
    Peer(PeerArguments* args);
    ~Peer();

    void setExc();
    bool getIsExc();
    void peerRequest(json request);
    void static peerCommunicator(PeerArguments* args, Peer* peer);
    void disconnectFromNode();
    Socket* getSocket();
    int getTransactionNumber();

};

#endif // !PEER_H