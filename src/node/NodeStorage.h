#ifndef NODESTORAGE_H
#define NODESTORAGE_H

#include "Node.h"
/**
 * @brief Peer table entry
 * 
 */
struct PeerRecord
{
    std::string username;
    std::string ip;
    unsigned short port;
    unsigned int timeout;
};

/**
 * @brief Node table entry
 * 
 */
struct NodeRecord
{
    Request* request;
    unsigned int timeout;
    std::vector<PeerRecord> peers; //json peers;
};

class Node;
/**
 * @brief Node storage class that holds node database
 * 
 */
class NodeStorage
{
private:
    Node* node;
    std::map<std::string, PeerRecord*> users_registerd;
    std::map<std::pair<std::string, unsigned int>, NodeRecord*> neighbors;
    std::vector<std::pair<std::string, unsigned int>> disconectedNeighbors;
    std::vector<unsigned short> acknowledgements;

    std::mutex regUsrsMutex, ackMutex, neighborsMutex, discNeighborsMutex;
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
    bool addNeighbor(std::string ipv4, unsigned int port, bool authority);
    bool deleteNeighbor(std::string ipv4, unsigned int port);
    void updateNeighborsPeers(std::pair<std::string, unsigned int> ip_port, std::vector<PeerRecord> peers);
    json getPeerRecords();
    json getDbRecords();
    std::map<std::pair<std::string, unsigned int>, NodeRecord*> getNeighbors();
    json getAllPeersRecords();
    void emptyNeighbors();
    void addDiscNeighbor(std::pair<std::string, unsigned int> ip_port);
    std::vector<std::pair<std::string, unsigned int>> getDiscNeighbors();
};

#endif // !NODESTORAGE_H