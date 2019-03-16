#include "RpcFunctions.h"

void onGetList(Peer* peer, json* data){
    unsigned short transactionNumber = peer->getTransactionNumber();
    json request = {
            {"type", "getlist"},
            {"txid", transactionNumber},
        };
    
    peer->sendSocket(request);
    peer->waitAck(request["txid"]);
}

void onPeers(Peer* peer, json* data){

    peer->setPeerDisp(true);
    onGetList(peer, data);
}

void onMessage(Peer* peer, json* data){
    peer->insertMessage(*data);
    onGetList(peer, data);
}

void onReconnect(Peer* peer, json* data){
    peer->reconect((*data)["ipv4"], (*data)["port"]);
}