#ifndef PEER_H
#define PEER_H

#include <map>
#include <string>

#include "../libs/json.hpp"
#include "common/ErrHandle.h"
#include "common/MyExceptions.h"

#include "PeerFunctions.h"

using json = nlohmann::json;

struct PeerRecord
{
    unsigned short id;
    std::string username;
    std::string ip;
    unsigned short port;
};


class Peer
{
private:
    //std::map<unsigned short, PeerRecord> users_registerd;
    //std::map<unsigned short, PeerRecord> users_abroad;
    
    typedef void (*argFunction) (Peer*, json*) ;
    std::map<std::string, argFunction > funcMap; 
    
    bool isExc;
public:
    Peer();
    ~Peer();

    void setExc();
    bool getIsExc();
    void peerRequest(json request);
};

#endif // !PEER_H