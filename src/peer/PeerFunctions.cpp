#include "PeerFunctions.h"

void onAck(Peer* peer, json data, Request* request){
    int transactionNumber = data["txid"];
    peer->insertAck(transactionNumber);
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
    if(!data["peers"].is_array())
        throw CustomException("Exception raised: Protocol not supported peers array not found");

    //check what to do
    if(peer->getPeerDist()){
        std::cout<<data.dump(2)<<std::endl;
        peer->setPeerDisp(false);
    }
    
    peer->sendMessages(data["peers"]);
    
}

void onMessage(Peer* peer, json data, Request* request){
    std::cout<<data.dump(2)<<std::endl;
}