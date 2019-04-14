#include "RpcFunctions.h"

void onDatabase(Node* node, json* data){
    json peerRecords = node->getStorage()->getAllPeersRecords();
    std::cout<<peerRecords.dump(2)<<std::endl;
}

void onNeighbors(Node* node, json* data){
    std::cout << "Node neighbors: " << std::endl;

    for(auto neighbor : node->getStorage()->getNeighbors())
    {
        std::cout << "IP: "+ neighbor.first.first+", port:" + std::to_string(neighbor.first.second)<<std::endl;
    }
    std::cout<<std::endl;
}

void onConnect(Node* node, json* data){
    std::string ipv4 = (*data)["ipv4"];
    unsigned int port = (*data)["port"];
    node->getStorage()->setDisc(false);
    // try to connect to node - authority is true
    if(!node->connectNode(ipv4, port, true)){
        throw LocalException("Already connected to %s,%d", ipv4.c_str(), port);
    }
}

void onDisconnect(Node* node, json* data){
    node->disconnect();
}

void onSync(Node* node, json* data){
    json update = {
            {"type", "update"}
        };
    update["db"] = node->getStorage()->getDbRecords();
    
    for(auto neighbor : node->getStorage()->getNeighbors())
    {
        update["txid"] = node->getStorage()->getTransactionNumber();
        node->sendSocket(update, neighbor.second->request);
    } 
}

void onDump(Node* node, json* data){
    std::cout << "DISCONECTED NEIGHBORS" << '\n';
    for(auto var : node->getStorage()->getDiscNeighbors())
    {
        std::cout << "IP: " << var.first <<" Port:" <<var.second << '\n';
    }

    std::cout << "NEIGHBORS" << '\n';
    for(auto var : node->getStorage()->getNeighbors())
    {
        std::cout << "IP: " << var.first.first <<" Port:" <<var.first.second << '\n';
        std::cout << "Timeout: " << var.second->timeout << '\n';
    }
}