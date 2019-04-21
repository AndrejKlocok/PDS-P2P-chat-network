#include "NodeFunctions.h"

/**
 * @brief Function handles onHello message
 * 
 * @param node 
 * @param data 
 * @param request 
 */
void onHello(Node* node, json data, Request* request){
    PeerRecord* record = new PeerRecord();

    record->username = data["username"];
    record->port = data["port"];
    record->timeout = 0;


    //client disconnected
    if(record->port == 0 && data["ipv4"] == "0.0.0.0"){
        node->getStorage()->incPeerTimer(record->username, 30);
        return;
    }

    record->ip = data["ipv4"];

    //if new record is created run timer
    if(node->getStorage()->addNewLocalPeer(record)){
        //timer will tick till it is > 30 or user logs out
        while(node->getStorage()->incPeerTimer(record->username, 1) && !node->getStorage()->getIsExc()){ 
            //wait 1s
            std::this_thread::sleep_for(std::chrono::seconds(1));
        };
    }    

}

/**
 * @brief Function handles onGetList message
 * 
 * @param node 
 * @param data 
 * @param request 
 */
void onGetList(Node* node, json data, Request* request){
    json ack ={
        {"type", "ack"},
        {"txid", data["txid"]}
    };
    //if peer is not connected ignore
    if(!node->getStorage()->isPeerLoggedIn(inet_ntoa(request->addr.sin_addr), ntohs(request->addr.sin_port))){
        throw GlobalException("Exception raised: Requestor %s:%d is not registered, Ignore", inet_ntoa(request->addr.sin_addr), ntohs(request->addr.sin_port));
    }
    
    //send ack
    node->sendSocket(ack, request);
    json peerRecords = node->getStorage()->getAllPeersRecords();

    //PEER_RECORD := {"<ushort>":{"username":"<string>", "ipv4":"<dotted_decimal_IP>", "port": <ushort>}}     
    int transactionNumber = node->getStorage()->getTransactionNumber();
    json listMsg ={
        {"type", "list"},
        {"txid", transactionNumber},
        {"peers", peerRecords}
    };
    node->sendSocketWait(listMsg, request);
}

/**
 * @brief Function handles onUpdate message
 * 
 * @param node 
 * @param data 
 * @param request 
 */
void onUpdate(Node* node, json data, Request* request){
    std::string ipv4 = std::string(inet_ntoa(request->addr.sin_addr));
    unsigned int port = ntohs(request->addr.sin_port);

    //try to connect to sender - authority
    node->connectNode(ipv4, port, true);
    
    auto ip_port = std::make_pair(ipv4, port);
    json db = data["db"];

    std::string aut_key = ipv4+","+std::to_string(port);
    //find autoritaive database and update
    for (json::iterator it = db.begin(); it != db.end(); ++it) {
        //autoritative database
        if(it.key() == aut_key){
            std::vector<PeerRecord> peers;
            //for each peer ("number")
            if(it.value().is_object()){
                for (json::iterator it_peer = it.value().begin(); it_peer != it.value().end(); ++it_peer){
                    PeerRecord peer;
                    try
                    {
                        peer.username = it_peer.value()["username"];
                        peer.ip = it_peer.value()["ipv4"];
                        peer.port = it_peer.value()["port"];
                        peers.push_back(peer);
                    }
                    catch(const std::exception& e)
                    {
                        throw GlobalException("Protocol not supported: db entries");
                    }
                }  
            }
            node->getStorage()->updateNeighborsPeers(ip_port, peers); 
        //try fullhash (not with me ofc)
        }else {
            size_t pos = 0;
            std::string ipv4_tmp;
            unsigned int port_tmp;
            if ((pos = it.key().find(",")) != std::string::npos) {
                ipv4_tmp = it.key().substr(0, pos);
                port_tmp = atoi(it.key().substr(pos+1).c_str());
                
                // try to connect to neighbor - authority is false
                node->connectNode(ipv4_tmp, port_tmp, false);
            }
            else{
                throw GlobalException("Protocol not supported: db entries");
            }
        }
    }
}

/**
 * @brief Function handles onDisconnect message
 * 
 * @param node 
 * @param data 
 * @param request 
 */
void onDisconnect(Node* node, json data, Request* request){
    json ack ={
        {"type", "ack"},
        {"txid", data["txid"]}
    };
    node->sendSocket(ack, request);

    std::string ipv4 = std::string(inet_ntoa(request->addr.sin_addr));
    unsigned int port = ntohs(request->addr.sin_port);

    node->getStorage()->deleteNeighbor(ipv4, port);
}

/**
 * @brief Function handles onAck message
 * 
 * @param node 
 * @param data 
 * @param request 
 */
void onAck(Node* node, json data, Request* request){
    int transactionNumber = data["txid"];
    //store acnkonwledgemet
    node->getStorage()->insertAck(transactionNumber);
}

/**
 * @brief Function handles onError message
 * 
 * @param node 
 * @param data 
 * @param request 
 */
void onError(Node* node, json data, Request* request){
    int transactionNumber = data["txid"];
    std::string verbose = data["verbose"];

    std::cerr<<"txid: " << transactionNumber<< ", " << verbose << std::endl;
}