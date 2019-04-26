#include "RpcFunctions.h"

/**
 * @brief Prints database of neighboring nodes with peers
 * 
 * @param node 
 * @param data 
 */
void onDatabase(Node* node, json* data){
    std::cout << "------------<Database>------------" << '\n';
    auto local = node->getStorage()->getUsersRegistered();
    for(auto peer : local)
    {
        std::cout << peer.first<<","<<peer.second->ip<<":"<<peer.second->port << '\n';
    }
    std::cout << "----------<Other nodes>-----------" << '\n';
    auto neighbors = node->getStorage()->getNeighbors();
    for(auto neighbor : neighbors)
    {
        std::cout << "Node:" <<neighbor.first.first <<":"<<neighbor.first.second<< '\n';
        for(auto peer : neighbor.second->peers)
        {
            std::cout << "\t"<< peer.username << ", " << peer.ip<<":"<<peer.port << '\n';
        }
        
    }
    std::cout << "----------------------------------" << '\n';
}
/**
 * @brief Prints neighboring nodes
 * 
 * @param node 
 * @param data 
 */
void onNeighbors(Node* node, json* data){
    std::cout << "Node neighbors: " << std::endl;

    for(auto neighbor : node->getStorage()->getNeighbors())
    {
        std::cout << "IP: "+ neighbor.first.first+", port:" + std::to_string(neighbor.first.second)<<std::endl;
    }
    std::cout<<std::endl;
}

/**
 * @brief Connect node to other node described in json data
 * 
 * @param node 
 * @param data json
 */
void onConnect(Node* node, json* data){
    std::string ipv4 = (*data)["ipv4"];
    unsigned int port = (*data)["port"];
    node->getStorage()->setDisc(false);
    // try to connect to node - authority is true
    if(!node->connectNode(ipv4, port, true)){
        throw LocalException("Already connected to %s,%d", ipv4.c_str(), port);
    }
}
/**
 * @brief Disconnects from mesh
 * 
 * @param node 
 * @param data 
 */
void onDisconnect(Node* node, json* data){
    node->disconnect();
}

/**
 * @brief Forces db synchronisation
 * 
 * @param node 
 * @param data 
 */
void onSync(Node* node, json* data){
    json update = {
            {"type", "update"}
        };
    update["db"] = node->getStorage()->getDbRecords();
    // send update to neighboring nodes
    for(auto neighbor : node->getStorage()->getNeighbors())
    {
        update["txid"] = node->getStorage()->getTransactionNumber();
        node->sendSocket(update, neighbor.second->request);
    } 
}
