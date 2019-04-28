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

/**
 * @brief Returns peer records with node mapping in json format
 * 
 * @return json 
 */
json NodeStorage::getDbRecords(){
    json db;
    int i;
    //get unauthorized peer records
    std::scoped_lock(neighborsMutex);
    // each peer entry in this format
    // {"<ushort>":{"username":"<string>", "ipv4":"<dotted_decimal_IP>", "port": <ushort>}}  
    
    for( auto it = neighbors.begin(); it != neighbors.end(); ++it ) {
        json neighbor;
        i = 0;
        for(auto peerRecord : it->second->peers)
        {
            json p ={
                {"username", peerRecord.username},
                {"ipv4", peerRecord.ip},
                {"port", peerRecord.port}
            };
            neighbor[std::to_string(i)]= p;
            i++;
        }

        db[it->first.first+","+std::to_string(it->first.second)]=neighbor;
    }
    //get authorized peer records
    NodeArguments* args = node->getArguments();
    db[args->regIpv4+","+std::to_string(args->regPort)] = getPeerRecords();

    return db;
}

/**
 * @brief Function returns just registered peers.
 * 
 * @return json 
 */
json NodeStorage::getPeerRecords(){
    json peerRecords;
    int i = 0;
    //registred users on the node
    // each peer entry in this format
    // {"<ushort>":{"username":"<string>", "ipv4":"<dotted_decimal_IP>", "port": <ushort>}}  
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

/**
 * @brief Return peer recors in json format
 * 
 * @return json 
 */
json NodeStorage::getAllPeersRecords(){
    json peers;
    int i = 0;
    //registred peers on the node
    for( auto it = users_registerd.begin(); it != users_registerd.end(); ++it ) {
        json p ={
            {"username", it->second->username},
            {"ipv4", it->second->ip},
            {"port", it->second->port}
        };
        peers[std::to_string(i)] = p;
        i++;
    }
    //neighbors peers
    for( auto it = neighbors.begin(); it != neighbors.end(); ++it ) {
        json neighbor;
        for(auto peerRecord : it->second->peers)
        {
            json p ={
                {"username", peerRecord.username},
                {"ipv4", peerRecord.ip},
                {"port", peerRecord.port}
            };
            peers[std::to_string(i)]= p;
            i++;
        }
    }
    return peers;
}

/**
 * @brief Register neighboring node to database
 * 
 * @param ipv4 
 * @param port 
 * @param authority 
 * @return true node registered
 * @return false already registered
 */
bool NodeStorage::addNeighbor(std::string ipv4, unsigned int port, bool authority){
    auto ip_port = std::make_pair(ipv4, port);
    
    //node was disconnected from neighborhood
    auto iter_disc = std::find(disconectedNeighbors.begin(), disconectedNeighbors.end(), ip_port);
    if(iter_disc != disconectedNeighbors.end()){
        //authority is true - connecting to author
        if(authority){
            //lock
            std::scoped_lock(discNeighborsMutex);
            disconectedNeighbors.erase(iter_disc);
        }
        //authority is false - connecting to neighbor
        else
            return false;
    }

    auto iter = neighbors.find(ip_port);

    //if user is connected reset
    if(iter != neighbors.end()){ 

         if(authority){
            std::scoped_lock(neighborsMutex);
            iter->second->timeout = 0;  
        }
        return false;
    }
    // register node
    std::scoped_lock(neighborsMutex);

    NodeRecord* record = new NodeRecord();
    record->request = Socket::createRequest(ipv4, port);
    record->timeout = 0;

    this->neighbors[ip_port] = record;
    return true;
}
/**
 * @brief Increase timer for node ip_port by time
 * 
 * @param ip_port node identification
 * @param time  ammount of time
 * @return true  time increased
 * @return false node was not found or timeout
 */
bool NodeStorage::incNodeTimer(std::pair<std::string, unsigned int> ip_port, int time){
    
    auto iter = neighbors.find(ip_port);
    if(iter != neighbors.end()){
        if(iter->second->timeout > 12){
            std::scoped_lock(neighborsMutex);
            this->neighbors.erase(iter);
            return false;
        }
        iter->second->timeout += time;
        return true;
    }
    return false;
}
/**
 * @brief Remove node from neighborhood.
 * 
 * @param ipv4 nodes ip
 * @param port  nodes port
 * @return true  successfull
 * @return false node was not found
 */
bool NodeStorage::deleteNeighbor(std::string ipv4, unsigned int port){
    auto ip_port = std::make_pair(ipv4, port);
    
    auto iter = neighbors.find(ip_port);

    //if user is connected
    if(iter != neighbors.end()){
        //if node is disconnecting do nothing else notify that node is disconnected
        if(!getIsDisc()){
            addDiscNeighbor(ip_port);
        }
        std::scoped_lock(neighborsMutex); 
        neighbors.erase(iter);
        return true;
    }

    return false;
}
/**
 * @brief Getter
 * 
 */
void NodeStorage::emptyNeighbors(){
    this->neighbors.clear();
}

/**
 * @brief Getter
 * 
 * @return std::map<std::pair<std::string, unsigned int>, NodeRecord*> 
 */
std::map<std::pair<std::string, unsigned int>, NodeRecord*> NodeStorage::getNeighbors(){
    return neighbors;
}

/**
 * @brief Update neighboring node database
 * 
 * @param ip_port node identification
 * @param peers 
 */
void NodeStorage::updateNeighborsPeers(std::pair<std::string, unsigned int> ip_port, std::vector<PeerRecord> peers){
    
    auto iter = neighbors.find(ip_port);
    if(iter != neighbors.end()){ 
        std::scoped_lock(neighborsMutex);
        iter->second->peers = peers;   
    }
}

/**
 * @brief Register local peer
 * 
 * @param record Peer structure
 * @return true peer created
 * @return false peer connected -> resets timeout
 */
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
/**
 * @brief Increase timer of peer by time
 * 
 * @param username peer
 * @param time ammout of time
 * @return true timer increased
 * @return false timeout
 */
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

/**
 * @brief Acknowledge message
 * 
 * @param txid 
 * @return true successfull
 * @return false acknowledgement was not found
 */
bool NodeStorage::acknowledge(unsigned short txid){
    auto iter = find (acknowledgements.begin(), acknowledgements.end(), txid);
    
    //acknowledgement was not found
    if(iter == acknowledgements.end())
        return false;

    std::scoped_lock(ackMutex);
    acknowledgements.erase(iter);
    return true;
}

/**
 * @brief Insert acknowledgement
 * 
 * @param txid 
 */
void NodeStorage::insertAck(unsigned short txid){
    std::scoped_lock(ackMutex);
    acknowledgements.push_back(txid);
}

/**
 * @brief Check if peer is registered
 * 
 * @param ip peer IP
 * @param port  peer PORT
 * @return true peer is registered
 * @return false peer is unknown
 */
bool NodeStorage::isPeerLoggedIn(std::string ip, unsigned short port){
    
    for( std::map<std::string, PeerRecord*>::iterator it = users_registerd.begin(); it != users_registerd.end(); ++it )
        if(it->second->ip == ip && it->second->port == port)
            return true;
    return false;
}

/**
 * @brief Check if node is up
 * 
 * @param ip_port 
 * @return true 
 * @return false 
 */
bool NodeStorage::isNodeAlive(std::pair<std::string, unsigned int> ip_port){
    auto iter = neighbors.find(ip_port);

    //if user is in map
    if(iter != neighbors.end()){ 
       return true;
    }
    return false;
}

/**
 * @brief Handles disconnect of node from mesh
 * 
 * @param ip_port 
 */
void NodeStorage::addDiscNeighbor(std::pair<std::string, unsigned int> ip_port){
    auto iter_disc = std::find(disconectedNeighbors.begin(), disconectedNeighbors.end(), ip_port);
    
    //disc neighbor is not in vector (no duplicates...)
    if(iter_disc == disconectedNeighbors.end()){
        std::scoped_lock(discNeighborsMutex); 
         disconectedNeighbors.push_back(ip_port);
    }
}

/**
 * @brief Set exc status
 * 
 */
void NodeStorage::setExc(){
    this->isExc = true;
    this->isDisc = true;
}

/**
 * @brief Getter
 * 
 * @return true 
 * @return false 
 */
bool NodeStorage::getIsExc(){
    return this->isExc;
}
/**
 * @brief Getter
 * 
 * @return unsigned short 
 */
unsigned short NodeStorage::getTransactionNumber(){
    return transactionNumber++;
}

/**
 * @brief Setter
 * 
 * @param disc 
 */
void NodeStorage::setDisc(bool disc){
    this->isDisc = disc;
}

/**
 * @brief Getter
 * 
 * @return true 
 * @return false 
 */
bool NodeStorage::getIsDisc(){
    return isDisc;
}
/**
 * @brief Getter
 * 
 * @return std::vector<std::pair<std::string, unsigned int>> 
 */
std::vector<std::pair<std::string, unsigned int>> NodeStorage::getDiscNeighbors(){
    return disconectedNeighbors;
}
/**
 * @brief Getter
 * 
 * @return std::map<std::string, PeerRecord*> 
 */
std::map<std::string, PeerRecord*> NodeStorage::getUsersRegistered(){
    return users_registerd;
}