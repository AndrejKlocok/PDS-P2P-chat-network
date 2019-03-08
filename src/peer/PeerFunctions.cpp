#include "PeerFunctions.h"

void onList(Peer* peer, json data, Request* request, Socket* socket){
    //send all messages from vector of messages
}

void onAck(Peer* peer, json data, Request* request, Socket* socket){
    int transactionNumber = data["txid"];
    peer->insertAck(transactionNumber);
}

void onError(Peer* peer, json data, Request* request, Socket* socket){
    int transactionNumber = data["txid"];
    std::string verbose = data["verbose"];

    std::cerr<<"txid: " << transactionNumber<< ", " << verbose << std::endl;
}