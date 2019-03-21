#include "PeerFunctions.h"

void onAck(Peer* peer, json data, Request* request){
    int transactionNumber = data["txid"];
    peer->getStorage()->insertAck(transactionNumber);
}

void onError(Peer* peer, json data, Request* request){
    int transactionNumber = data["txid"];
    std::string verbose = data["verbose"];

    std::cerr<<"txid: " << transactionNumber<< ", " << verbose << std::endl;
}

void onList(Peer* peer, json data, Request* request){
    json ack ={
        {"type", "ack"},
        {"txid", data["txid"]}
    };
    //send ack
    peer->sendSocket(ack);
    //look for peers
    if(!data["peers"].is_object())
        throw CustomException("Exception raised: Protocol not supported peers dictionary not found");

    //check what to do
    if(peer->getStorage()->getPeerDist()){
        std::cout<<data.dump(2)<<std::endl;
        peer->getStorage()->setPeerDisp(false);
    }
    
    peer->getStorage()->sendMessages(data["peers"]);
    
}

void onMessage(Peer* peer, json data, Request* request){
    json ack ={
        {"type", "ack"},
        {"txid", data["txid"]}
    };
    peer->sendSocket(ack, request);
    std::cout<<data.dump(2)<<std::endl;
}