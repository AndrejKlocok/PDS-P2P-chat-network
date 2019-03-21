#include "RpcFunctions.h"

void onGetList(Peer* peer, json* data){
    unsigned short transactionNumber = peer->getStorage()->getTransactionNumber();
    json request = {
            {"type", "getlist"},
            {"txid", transactionNumber},
        };
    peer->sendSocketWait(request);
}

void onPeers(Peer* peer, json* data){

    peer->getStorage()->setPeerDisp(true);
    onGetList(peer, data);
}

void onMessage(Peer* peer, json* data){
    peer->getStorage()->insertMessage(*data);
    onGetList(peer, data);
}

void onReconnect(Peer* peer, json* data){
    peer->reconect((*data)["ipv4"], (*data)["port"]);
}