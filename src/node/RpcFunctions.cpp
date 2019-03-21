#include "RpcFunctions.h"

void onDatabase(Node* node, json* data){
    json peerRecords = node->getStorage()->getPeerRecords();
    std::cout<<peerRecords.dump(2)<<std::endl;
}

void onNeighbors(Node* node, json* data){
    std::cout<<node->getStorage()->getDbRecords().dump(2)<<std::endl;
}

void onConnect(Node* node, json* data){
    std::string ipv4 = (*data)["ipv4"];
    unsigned int port = (*data)["port"];
    node->getStorage()->setDisc(false);
    if(!node->connectNode(ipv4, port)){
        throw CustomException("Already connected to %s,%d", ipv4.c_str(), port);
    }
}

void onDisconnect(Node* node, json* data){
    node->disconnect();
}

void onSync(Node* node, json* data){
    
}