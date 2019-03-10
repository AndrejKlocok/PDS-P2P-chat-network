#include "Node.h"

Node::Node()
{
    this->isExc = false;
    rpcMap["onDatabase"]     = onDatabase;
    rpcMap["onNeighbors"]    = onNeighbors;
    rpcMap["onConnect"]      = onConnect;
    rpcMap["onDisconnect"]   = onDisconnect;
    rpcMap["onSync"]         = onSync;

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
    std::pair<std::string,unsigned short> ip_port = std::make_pair(record->ip, record->port);
    Socket* socket = new Socket(record->ip, record->port);

    std::scoped_lock(regUsrsMutex);
    this->users_registerd[record->username]= record;
    this->users_socket[ip_port] = socket;

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
            std::pair<std::string,unsigned short> ip_port = std::make_pair(iter->second->ip, iter->second->port);
            //find socket object
            auto soc_iter = users_socket.find(ip_port);
            //if there is socket obj delete both
            if(soc_iter != users_socket.end()){ 
                std::scoped_lock(regUsrsMutex);
                users_registerd.erase(iter);
                users_socket.erase(soc_iter);
            }
            //this option should not have exist but in case 
            else
            {
                std::scoped_lock(regUsrsMutex);
                users_registerd.erase(iter);
            }
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

Socket* Node::getPeerSocket(std::string Ip, unsigned short port){
    std::pair<std::string,unsigned short> ip_port = std::make_pair(Ip, port);
    auto iter = users_socket.find(ip_port);
    if(iter == users_socket.end())
        throw CustomException("Exception raised; Ip: %s :%d not found", Ip.c_str(), port);
    
    return iter->second;
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