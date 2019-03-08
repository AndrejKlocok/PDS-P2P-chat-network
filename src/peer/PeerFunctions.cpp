#include "PeerFunctions.h"

void onGetList(Peer* peer, json* data){
    json request = {
            {"type", "getlist"},
            {"txid", peer->getTransactionNumber()},
        };
    
    peer->getSocket()->sendData(request);
    
}

void onPeers(Peer* peer, json* data){

}

void onMessage(Peer* peer, json* data){

}

void onReconnect(Peer* peer, json* data){

}