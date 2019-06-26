/**
 * @file PeerStorage.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#ifndef PEERSTORAGE_H
#define PEERSTORAGE_H

#include <mutex>
#include <deque>

#include "Peer.h"

class Peer;

/**
 * @brief Peer storage class
 * 
 */
class PeerStorage
{
private:
    Peer* peer;
    bool isExc, isHello;
    bool peersDisp;
    std::deque<json> messages;
    std::mutex msgMutex, ackMutex;
    unsigned short transactionNumber;
    std::vector<unsigned short> acknowledgements;
public:
    PeerStorage(Peer* peer);
    ~PeerStorage();

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


#endif // !PEERSTORAGE_H