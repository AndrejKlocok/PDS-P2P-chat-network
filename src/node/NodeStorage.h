#ifndef NODESTORAGE_H
#define NODESTORAGE_H

#include "Node.h"

struct PeerRecord
{
    std::string username;
    std::string ip;
    unsigned short port;
    unsigned int timeout;
};

struct NodeRecord
{
    Request* request;
    unsigned int timeout;
    json peers;//std::vector<PeerRecord> peers;
};

class Node;
class NodeStorage
{
private:
    Node* node;
    std::map<std::string, PeerRecord*> users_registerd;
    std::map<std::pair<std::string, unsigned int>, NodeRecord*> neighbors;
    std::vector<unsigned short> acknowledgements;

    std::mutex regUsrsMutex, ackMutex, neighborsMutex;
    bool isExc, isDisc;
    unsigned short transactionNumber;
public:
    NodeStorage(Node* node);
    ~NodeStorage();
    
    void setExc();
    bool getIsExc();
    void setDisc(bool disc);
    bool getIsDisc();
    bool addNewLocalPeer(PeerRecord* record);
    bool incPeerTimer(std::string username, int time);
    bool incNodeTimer(std::pair<std::string, unsigned int> ip_port, int time);
    unsigned short getTransactionNumber();
    bool acknowledge(unsigned short txid);
    void insertAck(unsigned short txid);
    bool isPeerLoggedIn(std::string ip, unsigned short port);
    bool isNodeAlive(std::pair<std::string, unsigned int> ip_port);
    bool addNeighbor(std::string ipv4, unsigned int port);
    bool deleteNeighbor(std::string ipv4, unsigned int port);
    void updateNeighborsPeers(std::pair<std::string, unsigned int> ip_port, json peers);
    json getPeerRecords();
    json getDbRecords();
    std::map<std::pair<std::string, unsigned int>, NodeRecord*> getNeighbors();
    void emptyNeighbors();
};

#endif // !NODESTORAGE_H