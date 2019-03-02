#include "Peer.h"

Peer::Peer()
{
    this->isExc = false;
    //funcMap["database"]     = onDatabase;
    
}

Peer::~Peer(){}


void Peer::peerRequest(json request){

    /*if(request["txid"] != this->id){
        throw PeerWrongId();
    }*/
    //find desired action in map of actions
    auto iter = funcMap.find(request["type"]);

    //call function
    if(iter != funcMap.end()){
        iter->second(this, &request);
    }
    else{
        throw UnknownType();
    }
}

void Peer::setExc(){
    this->isExc = true;
}

bool Peer::getIsExc(){
    return this->isExc;
}