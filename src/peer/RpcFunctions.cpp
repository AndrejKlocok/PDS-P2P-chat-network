#include "RpcFunctions.h"

void onGetList(Peer* peer, json* data){
    unsigned short transactionNumber = peer->getTransactionNumber();
    json request = {
            {"type", "getlist"},
            {"txid", transactionNumber},
        };
    
    peer->sendSocket(request);
    
    // wait for ack 
    /*json response = socket->recvData();

    peer->request(response, socket->getRequest(), socket);

     if(!peer->acknowledge(transactionNumber)){
        throw CustomException("Exception raised: Getlist, ack %d not received", transactionNumber);
    }*/
}

void onPeers(Peer* peer, json* data){

}

void onMessage(Peer* peer, json* data){

}

void onReconnect(Peer* peer, json* data){

}