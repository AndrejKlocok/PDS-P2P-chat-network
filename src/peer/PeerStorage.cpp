/**
 * @file PeerStorage.cpp
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#include "PeerStorage.h"

PeerStorage::PeerStorage(Peer* peer)
{
    this->peer = peer;
    this->isExc = false;
    this->isHello = false;
    this->peersDisp = false;
    this->transactionNumber = 0;
}

PeerStorage::~PeerStorage()
{
}
/**
 * @brief Method inserts new message, which will be sent when LIST msg arrives.
 * 
 * @param message 
 */
void PeerStorage::insertMessage(json message){
    std::scoped_lock(msgMutex);
    this->messages.push_back(message);
}

/**
 * @brief Lookup consignee and send him message
 * 
 * @param peers 
 */
void PeerStorage::sendMessages(json peers){
   json msg = getFrontMessage();

    for (auto& [key, value] : peers.items()) {
        if(msg["to"] == value["username"]){
            (void)key;
            msg["txid"] = getTransactionNumber();
            Request* consignee = Socket::createRequest(value["ipv4"], value["port"]);
            peer->sendSocketWait(msg, consignee);
            return;
        }
    }
    //Message was not sent
    std::string to = msg["to"];
    throw LocalException("Exception raised: %s is not accessible", to.c_str());
}

/**
 * @brief Get message from FIFO queue
 * 
 * @return json message
 */
json PeerStorage::getFrontMessage(){
    json msg;

    if(messages.empty()){
        throw PeerMsgEmpty();
    }
    else{
        std::scoped_lock(msgMutex);
        msg = messages.front();
        messages.pop_front();
    }
    
    return msg;
}
/**
 * @brief Increment txid and return
 * 
 * @return unsigned short 
 */
unsigned short PeerStorage::getTransactionNumber(){
    transactionNumber++;
    return transactionNumber;
}
/**
 * @brief Acknowledge message with txid
 * 
 * @param txid number of message
 * @return true acknowledged
 * @return false ack not found
 */
bool PeerStorage::acknowledge(unsigned short txid){
    auto iter = find (acknowledgements.begin(), acknowledgements.end(), txid);
    
    //acknowledgement was not found
    if(iter == acknowledgements.end())
        return false;

    std::scoped_lock(ackMutex);
    acknowledgements.erase(iter);
    return true;
}

/**
 * @brief Store ack
 * 
 * @param txid 
 */
void PeerStorage::insertAck(unsigned short txid){
    std::scoped_lock(ackMutex);
    acknowledgements.push_back(txid);
}

/**
 * @brief Wait 2s and check for ack
 * 
 * @param ackNumber 
 */
void PeerStorage::waitAck(int ackNumber){
    // wait for ack 
    std::this_thread::sleep_for(std::chrono::seconds(2));

     if(!acknowledge(ackNumber)){
        throw GlobalException("Exception raised: ack %d not received", ackNumber);
    }
}

/**
 * @brief Setter
 * 
 */
void PeerStorage::setExc(){
    this->isExc = true;
    this->isHello = true;
}
/**
 * @brief Getter
 * 
 * @return true 
 * @return false 
 */
bool PeerStorage::getIsExc(){
    return this->isExc;
}
/**
 * @brief Getter
 * 
 * @return true 
 * @return false 
 */
bool PeerStorage::getHello(){
    return this->isHello;
}
/**
 * @brief Setter
 * 
 * @param value 
 */
void PeerStorage::setHello(bool value){
    this->isHello = value;
}
/**
 * @brief Getter
 * 
 * @return true 
 * @return false 
 */
bool PeerStorage::getPeerDist(){
    return this->peersDisp;
}
/**
 * @brief Setter
 * 
 * @param value 
 */
void PeerStorage::setPeerDisp(bool value){
    this->peersDisp = value;
}