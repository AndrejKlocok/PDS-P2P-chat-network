#include "Node.h"

Node::Node()
{
    this->isExc = false;
    rpcMap["database"]     = onDatabase;
    rpcMap["neighbors"]    = onNeighbors;
    rpcMap["connect"]      = onConnect;
    rpcMap["disconnect"]   = onDisconnect;
    rpcMap["sync"]         = onSync;

    requestMap["hello"]        = onHello; 
    requestMap["getlist"]      = onGetList;
    requestMap["error"]        = onError;
}

Node::~Node(){}


void Node::rpcRequest(json* request, json* response){
    //find desired action in map of actions
    auto iter = rpcMap.find( (*request)["type"]);

    //call function
    if(iter != rpcMap.end()){
        iter->second(this, request, response);
    }
    else{
        throw UnknownType();
    }
}

void Node::request(json data, Request* request, Socket* socket){

    //find desired action in map of actions
    auto iter = requestMap.find( data["type"]);

    //call function
    if(iter != requestMap.end()){ 
        iter->second(this, data, request, socket);
    }
    else{
        throw UnknownType();
    }
}

bool Node::addNewLocalPeer(PeerRecord* record){
    //find user in users map
    auto iter = users_registerd.find(record->username);

    //if user is connected
    if(iter != users_registerd.end()){ 
        iter->second->timeout = 0;
        return false;
    }
    
    std::scoped_lock(regUsrsMutex);
    this->users_registerd[record->username]= record;

    return true;
}

bool Node::incPeerTimer(std::string username, int time){
    
    //find user in users map
    auto iter = users_registerd.find(username);

    //if user is in map
    if(iter != users_registerd.end()){ 
       //inc timer
       iter->second->timeout += time;
       //if timer value is greater than 30s remove entry
       if(iter->second->timeout > 30){
           users_registerd.erase(iter);
            return false;
       }
       return true;
    }
    return false;
}

bool Node::acknowledge(unsigned short txid){
    auto iter = find (acknowledgements.begin(), acknowledgements.end(), txid);
    
    //acknowledgement was not found
    if(iter == acknowledgements.end())
        return false;

    std::scoped_lock(ackMutex);
    acknowledgements.erase(iter);
    return true;
}

void Node::insertAck(unsigned short txid){
    std::scoped_lock(ackMutex);
    acknowledgements.push_back(txid);
}

std::vector<PeerRecord*> Node::getUsersVec(){
    std::vector<PeerRecord*> peers;
    
    for( std::map<std::string, PeerRecord*>::iterator it = users_registerd.begin(); it != users_registerd.end(); ++it ) {
        peers.push_back( it->second );
    }
    return peers;
}

void Node::setExc(){
    this->isExc = true;
}

bool Node::getIsExc(){
    return this->isExc;
}

unsigned short Node::getTransactionNumber(){
    return transactionNumber++;
}