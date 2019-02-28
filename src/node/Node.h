#ifndef NODE_H
#define NODE_H

#include <map>

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
    unsigned short id;
    bool isExc;
public:
    Node(unsigned short id);
    ~Node();
    unsigned short getId();
    void setExc();
    bool getIsExc();
};

#endif // !NODE_H