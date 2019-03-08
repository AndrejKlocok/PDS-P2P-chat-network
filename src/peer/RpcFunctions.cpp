#include "RpcFunctions.h"

void onGetList(Peer* peer, json* data){
    unsigned short transactionNumber = peer->getTransactionNumber();
    json request = {
            {"type", "getlist"},
            {"txid", transactionNumber},
        };
    
    peer->getSocket()->sendData(request);
    
    // wait for ack
    std::this_thread::sleep_for(std::chrono::seconds(2));
     if(!peer->acknowledge(transactionNumber)){
        throw CustomException("Exception raised: Getlist, ack %d not received", transactionNumber);
    }
}

void onPeers(Peer* peer, json* data){

}

void onMessage(Peer* peer, json* data){

}

void onReconnect(Peer* peer, json* data){

}