#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>

#include "../libs/json.hpp"
#include "common/ErrHandle.h"
#include "common/MyExceptions.h"

#include "NodeFunctions.h"

using json = nlohmann::json;

struct PeerRecord
{
    unsigned short id;
    std::string username;
    std::string ip;
    unsigned short port;
};


class Node
{
private:
    std::map<unsigned short, PeerRecord> users_registerd;
    std::map<unsigned short, PeerRecord> users_abroad;
    
    typedef void (*argFunction) (Node*, json*) ;
    std::map<std::string, argFunction > funcMap; 
    
    bool isExc;
public:
    Node();
    ~Node();

    void setExc();
    bool getIsExc();
    void nodeRequest(json request);
};

#endif // !NODE_H