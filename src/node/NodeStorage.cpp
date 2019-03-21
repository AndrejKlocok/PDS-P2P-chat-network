#include "NodeStorage.h"

NodeStorage::NodeStorage(Node* node)
{
    this->node = node;
    this->isExc = false;
    this->isDisc = false;
}

NodeStorage::~NodeStorage()
{
}

json NodeStorage::getDbRecords(){
    json db;
    //int i;
    //get unauthorized peer records
    std::scoped_lock(neighborsMutex);
    for( auto it = neighbors.begin(); it != neighbors.end(); ++it ) {
        json neighbor;
        //i = 0;
        /*for(auto peerRecord : it->second->peers)
        {
            json p ={
                {"username", peerRecord.username},
                {"ipv4", peerRecord.ip},
                {"port", peerRecord.port}
            };
            neighbor[std::to_string(i)]= p;
            i++;
        }*/

        db[it->first.first+","+std::to_string(it->first.second)]=it->second->peers;
    }
    //get authorized peer records
    NodeArguments* args = node->getArguments();
    db[args->regIpv4+","+std::to_string(args->regPort)] = getPeerRecords();

    return db;
}

json NodeStorage::getPeerRecords(){
    json peerRecords;
    int i = 0;
    
    for( auto it = users_registerd.begin(); it != users_registerd.end(); ++it ) {
        json p ={
            {"username", it->second->username},
            {"ipv4", it->second->ip},
            {"port", it->second->port}
        };
        peerRecords[std::to_string(i)] = p;
        i++;
    }
    return peerRecords;
}

bool NodeStorage::addNeighbor(std::string ipv4, unsigned int port){
    auto ip_port = std::make_pair(ipv4, port);
    
    std::scoped_lock(neighborsMutex);
    auto iter = neighbors.find(ip_port);

    //if user is connected
    if(iter != neighbors.end()){ 
        return false;
    }
    NodeRecord* record = new NodeRecord();
    record->request = Socket::createRequest(ipv4, port);
    record->timeout = 0;
    record->peers = nullptr;

    this->neighbors[ip_port] = record;

    return true;
}

bool NodeStorage::incNodeTimer(std::pair<std::string, unsigned int> ip_port, int time){
    std::scoped_lock(neighborsMutex);
    auto iter = neighbors.find(ip_port);

    if(iter != neighbors.end()){
        if(iter->second->timeout > 12){
            this->neighbors.erase(iter);

            return false;
        }
        iter->second->timeout += time;
        return true;
    }
    return false;
}

bool NodeStorage::deleteNeighbor(std::string ipv4, unsigned int port){
    auto ip_port = std::make_pair(ipv4, port);
    
    std::scoped_lock(neighborsMutex); 
    auto iter = neighbors.find(ip_port);

    //if user is connected
    if(iter != neighbors.end()){ 
        neighbors.erase(iter);
        return true;
    }

    return false;
}

void NodeStorage::emptyNeighbors(){
    this->neighbors.clear();
}

std::map<std::pair<std::string, unsigned int>, NodeRecord*> NodeStorage::getNeighbors(){
    return neighbors;
}

void NodeStorage::updateNeighborsPeers(std::pair<std::string, unsigned int> ip_port, json peers){
    std::scoped_lock(neighborsMutex);
    auto iter = neighbors.find(ip_port);
    if(iter != neighbors.end()){ 
        iter->second->timeout = 0;
        iter->second->peers = peers;   
    }
}

bool NodeStorage::addNewLocalPeer(PeerRecord* record){
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

bool NodeStorage::incPeerTimer(std::string username, int time){
    
    //find user in users map
    auto iter = users_registerd.find(username);

    //if user is in map
    if(iter != users_registerd.end()){ 
       //inc timer
       iter->second->timeout += time;
       //if timer value is greater than 30s remove entry
       if(iter->second->timeout > 30){
            std::scoped_lock(regUsrsMutex);
            users_registerd.erase(iter);
            
            return false;
       }
       return true;
    }
    return false;
}

bool NodeStorage::acknowledge(unsigned short txid){
    auto iter = find (acknowledgements.begin(), acknowledgements.end(), txid);
    
    //acknowledgement was not found
    if(iter == acknowledgements.end())
        return false;

    std::scoped_lock(ackMutex);
    acknowledgements.erase(iter);
    return true;
}

void NodeStorage::insertAck(unsigned short txid){
    std::scoped_lock(ackMutex);
    acknowledgements.push_back(txid);
}

bool NodeStorage::isPeerLoggedIn(std::string ip, unsigned short port){
    for( std::map<std::string, PeerRecord*>::iterator it = users_registerd.begin(); it != users_registerd.end(); ++it )
        if(it->second->ip == ip && it->second->port == port)
            return true;
    return false;
}

bool NodeStorage::isNodeAlive(std::pair<std::string, unsigned int> ip_port){
    auto iter = neighbors.find(ip_port);

    //if user is in map
    if(iter != neighbors.end()){ 
       return true;
    }
    return false;
}

void NodeStorage::setExc(){
    this->isExc = true;
    this->isDisc = true;
}

bool NodeStorage::getIsExc(){
    return this->isExc;
}

unsigned short NodeStorage::getTransactionNumber(){
    return transactionNumber++;
}

void NodeStorage::setDisc(bool disc){
    this->isDisc = disc;
}

bool NodeStorage::getIsDisc(){
    return isDisc;
}