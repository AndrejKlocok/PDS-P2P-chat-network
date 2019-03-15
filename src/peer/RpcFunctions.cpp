#include "RpcFunctions.h"

void onGetList(Peer* peer, json* data){
    unsigned short transactionNumber = peer->getTransactionNumber();
    json request = {
            {"type", "getlist"},
            {"txid", transactionNumber},
        };
    
    peer->sendSocket(request);
    
    // wait for ack 
    std::this_thread::sleep_for(std::chrono::seconds(1));

     if(!peer->acknowledge(transactionNumber)){
        throw CustomException("Exception raised: Getlist, ack %d not received", transactionNumber);
    }
}

void onPeers(Peer* peer, json* data){

    peer->setPeerDisp(true);
    onGetList(peer, data);
}

void onMessage(Peer* peer, json* data){
    
}

void onReconnect(Peer* peer, json* data){

}