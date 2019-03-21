#include "PeerStorage.h"

PeerStorage::PeerStorage(Peer* peer)
{
    this->peer = peer;
    this->isExc = false;
    this->isHello = false;
    this->transactionNumber = 0;
}

PeerStorage::~PeerStorage()
{
}

void PeerStorage::insertMessage(json message){
    std::scoped_lock(msgMutex);
    this->messages.push_back(message);
}

void PeerStorage::sendMessages(json peers){
   json msg = getFrontMessage();

    for (auto& [key, value] : peers.items()) {
        if(msg["to"] == value["username"]){
            (void)key;
            std::cout<<"Sending message\n";
            msg["txid"] = getTransactionNumber();
            Request* consignee = Socket::createRequest(value["ipv4"], value["port"]);
            peer->sendSocketWait(msg, consignee);
            break;
        }
    }
}

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

unsigned short PeerStorage::getTransactionNumber(){
    transactionNumber++;
    return transactionNumber;
}

bool PeerStorage::acknowledge(unsigned short txid){
    auto iter = find (acknowledgements.begin(), acknowledgements.end(), txid);
    
    //acknowledgement was not found
    if(iter == acknowledgements.end())
        return false;

    std::scoped_lock(ackMutex);
    acknowledgements.erase(iter);
    return true;
}

void PeerStorage::insertAck(unsigned short txid){
    std::scoped_lock(ackMutex);
    acknowledgements.push_back(txid);
}

void PeerStorage::waitAck(int ackNumber){
    // wait for ack 
    std::this_thread::sleep_for(std::chrono::seconds(2));

     if(!acknowledge(ackNumber)){
        throw CustomException("Exception raised: ack %d not received", ackNumber);
    }
}

void PeerStorage::setExc(){
    this->isExc = true;
    this->isHello = true;
}

bool PeerStorage::getIsExc(){
    return this->isExc;
}

bool PeerStorage::getHello(){
    return this->isHello;
}

void PeerStorage::setHello(bool value){
    this->isHello = value;
}

bool PeerStorage::getPeerDist(){
    return this->peersDisp;
}

void PeerStorage::setPeerDisp(bool value){
    this->peersDisp = value;
}