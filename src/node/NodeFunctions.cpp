#include "NodeFunctions.h"

void onHello(Node* node, json data, Request* request, Socket* socket){
    PeerRecord* record = new PeerRecord();

    record->username = data["username"];
    record->port = data["port"];
    record->timeout = 0;


    //client disconnected
    if(record->port == 0 && data["ipv4"].is_number()){
        //timeout
        //std::cout << "Disconected\n";
        node->incPeerTimer(record->username, 30);
        return;
    }

    record->ip = data["ipv4"];

    //if new record is created run timer
    if(node->addNewLocalPeer(record)){
        //std::cout << "New client\n";
        //timer will tick till it is > 30 or user logs out
        while(node->incPeerTimer(record->username, 1)){ 
            //wait 1s
            std::this_thread::sleep_for(std::chrono::seconds(1));
        };
        //std::cout << "Disconected timed out\n";
    }    

}

void onGetList(Node* node, json data, Request* request, Socket* socket){
    json ack ={
        {"type", "ack"},
        {"txid", data["txid"]}
    };

    //send ack
    socket->sendData(ack, request);
    json peerRecords;

    std::vector<PeerRecord*> peers = node->getUsersVec();
    
    for(auto peer : peers)
    {
        json p ={
            {"username", peer->username},
            {"ipv4", peer->ip},
            {"port", peer->port}
        };
        peerRecords.push_back(p);
    }

    //PEER_RECORD := {"<ushort>":{"username":"<string>", "ipv4":"<dotted_decimal_IP>", "port": <ushort>}}     
    int transactionNumber = node->getTransactionNumber();
    json listMsg ={
        {"type", "list"},
        {"txid", transactionNumber},
        {"peers", peerRecords}
    };

    socket->sendData(listMsg, request);
    
    //wait for ack
    std::this_thread::sleep_for(std::chrono::seconds(2));

    if(!node->acknowledge(transactionNumber)){
        throw CustomException("Exception raised: Getlist, ack %d not received", transactionNumber);
    }
}

void onAck(Node* node, json data, Request* request, Socket* socket){
    int transactionNumber = data["txid"];
    node->insertAck(transactionNumber);
}

void onError(Node* node, json data, Request* request, Socket* socket){
    int transactionNumber = data["txid"];
    std::string verbose = data["verbose"];

    std::cerr<<"txid: " << transactionNumber<< ", " << verbose << std::endl;
}