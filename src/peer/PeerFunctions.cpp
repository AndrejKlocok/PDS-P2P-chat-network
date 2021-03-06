/**
 * @file PeerFunctions.cpp
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#include "PeerFunctions.h"

/**
 * @brief Acknowledgement handler
 * 
 * @param peer 
 * @param data 
 * @param request 
 */
void onAck(Peer* peer, json data, Request* request){
    int transactionNumber = data["txid"];
    peer->getStorage()->insertAck(transactionNumber);
}
/**
 * @brief Error handler prints error 
 * 
 * @param peer 
 * @param data 
 * @param request 
 */
void onError(Peer* peer, json data, Request* request){
    int transactionNumber = data["txid"];
    std::string verbose = data["verbose"];

    std::cerr<<"txid: " << transactionNumber<< ", " << verbose << std::endl;
}
/**
 * @brief Handles list message according to set flags
 * 
 * @param peer 
 * @param data 
 * @param request 
 */
void onList(Peer* peer, json data, Request* request){
    json ack ={
        {"type", "ack"},
        {"txid", data["txid"]}
    };
    //send ack
    peer->sendSocket(ack, request);
    //look for peers
    if(!data["peers"].is_object())
        throw GlobalException("Exception raised: Protocol not supported peers dictionary not found");

    //check what to do
    if(peer->getStorage()->getPeerDist()){
        try
        {
            std::cout << "PEERS" << '\n';
            json db = data["peers"];
            for (json::iterator it = db.begin(); it != db.end(); ++it){
                std::cout << std::string(it.value()["username"]) <<","<< std::string(it.value()["ipv4"])<<":"<<it.value()["port"] << '\n';
                
            }
        }
        catch(const std::exception& e)
        {
            throw GlobalException("Exception raised: Wrong protocol structure");
        }
        
        peer->getStorage()->setPeerDisp(false);
    }
    
    peer->getStorage()->sendMessages(data["peers"]);
}
/**
 * @brief Message handle function prints message
 * 
 * @param peer 
 * @param data 
 * @param request 
 */
void onMessage(Peer* peer, json data, Request* request){    
    json ack ={
        {"type", "ack"},
        {"txid", data["txid"]}
    };
    peer->sendSocket(ack, request);
    
    try
    {
        std::cout << "New message from: "<<data["from"] << '\n';
        std::cout << data["message"] << '\n';
    }
    catch(const std::exception& e)
    {
        throw GlobalException("Exception raised: Wrong protocol structure");
    }
}