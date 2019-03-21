#include "NodeFunctions.h"

void onHello(Node* node, json data, Request* request){
    PeerRecord* record = new PeerRecord();

    record->username = data["username"];
    record->port = data["port"];
    record->timeout = 0;


    //client disconnected
    if(record->port == 0 && data["ipv4"].is_number()){
        //timeout
        //std::cout << "Disconected\n";
        node->getStorage()->incPeerTimer(record->username, 30);
        return;
    }

    record->ip = data["ipv4"];

    //if new record is created run timer
    if(node->getStorage()->addNewLocalPeer(record)){
        //std::cout << "New client\n";
        //timer will tick till it is > 30 or user logs out
        while(node->getStorage()->incPeerTimer(record->username, 1) && !node->getStorage()->getIsExc()){ 
            //wait 1s
            std::this_thread::sleep_for(std::chrono::seconds(1));
        };
        //std::cout << "Disconected timed out\n";
    }    

}

void onGetList(Node* node, json data, Request* request){
    json ack ={
        {"type", "ack"},
        {"txid", data["txid"]}
    };
    //if peer is not connected ignore
    if(!node->getStorage()->isPeerLoggedIn(inet_ntoa(request->addr.sin_addr), ntohs(request->addr.sin_port)))
        return;
    
    //send ack
    node->sendSocket(ack, request);
    json peerRecords = node->getStorage()->getPeerRecords();

    //PEER_RECORD := {"<ushort>":{"username":"<string>", "ipv4":"<dotted_decimal_IP>", "port": <ushort>}}     
    int transactionNumber = node->getStorage()->getTransactionNumber();
    json listMsg ={
        {"type", "list"},
        {"txid", transactionNumber},
        {"peers", peerRecords}
    };
    node->sendSocket(listMsg, request);
    //wait for ack
    std::this_thread::sleep_for(std::chrono::seconds(2));

    if(!node->getStorage()->acknowledge(transactionNumber)){
        throw CustomException("Exception raised: Getlist, ack %d not received", transactionNumber);
    }
}

void onUpdate(Node* node, json data, Request* request){
    std::string ipv4 = std::string(inet_ntoa(request->addr.sin_addr));
    unsigned int port = ntohs(request->addr.sin_port);

    node->connectNode(ipv4, port);
    
    auto ip_port = std::make_pair(ipv4, port);
    json db = data["db"];

    std::string key = ipv4+","+std::to_string(port);
    //find autoritaive database and update
    for (json::iterator it = db.begin(); it != db.end(); ++it) {
        if(it.key() == key){
            //for each peer ("number")
            if(it.value().is_object()){
                for (json::iterator it_test = it.value().begin(); it_test != it.value().end(); ++it_test){
                    //chceck json structure
                    if(!it_test.value()["username"].is_string() && 
                        !it_test.value()["port"].is_number() &&
                        !it_test.value()["ipv4"].is_string())
                    {
                        throw CustomException("Protocol not supported: db entries");
                    }
                }  
            }
            node->getStorage()->updateNeighborsPeers(ip_port, it.value()); 
        }else if(it.key() != node->getMe()){
            //try fullhash

            size_t pos = 0;
            std::string ipv4_tmp;
            unsigned int port_tmp;
            if ((pos = it.key().find(",")) != std::string::npos) {
                ipv4_tmp = it.key().substr(0, pos);
                port_tmp = atoi(it.key().substr(pos+1).c_str());

                node->connectNode(ipv4_tmp, port_tmp);
            }
            else{
                throw CustomException("Protocol not supported: db entries");
            }
        }
    }
}

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

void onAck(Node* node, json data, Request* request){
    int transactionNumber = data["txid"];
    node->getStorage()->insertAck(transactionNumber);
}

void onError(Node* node, json data, Request* request){
    int transactionNumber = data["txid"];
    std::string verbose = data["verbose"];

    std::cerr<<"txid: " << transactionNumber<< ", " << verbose << std::endl;
}