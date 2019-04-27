#include "Peer.h"

Peer::Peer(PeerArguments* args)
{
    this->peerArguments = args;
    this->requestAddr = Socket::createRequest(args->regIpv4, args->regPort);
    this->storage = new PeerStorage(this);
}

Peer::~Peer(){
    this->getStorage()->setExc();
    peerConnectionThread.join();
    disconnectFromNode();
    this->socket->~Socket();
}

/**
 * @brief Register rpc handle function
 * 
 * @param keyName 
 * @param func 
 */
void Peer::registerRpcRequest(std::string keyName, rpcFunction func){
    rpcMap[keyName] = func;
}

/**
 * @brief Register peer base function
 * 
 * @param keyName 
 * @param func 
 */
void Peer::registerBaseRequest(std::string keyName, baseFunction func){
    requestMap[keyName] = func;
}

/**
 * @brief Handle rpc request
 * 
 * @param request 
 */
void Peer::rpcRequest(json request){
    //find desired action in map of actions
    auto iter = rpcMap.find(request["type"]);

    //call function
    if(iter != rpcMap.end()){
        iter->second(this, &request);
    }
    else{
        throw UnknownType();
    }
}

/**
 * @brief Handles protocol messages from other peers or nodes
 * 
 * @param data 
 * @param request 
 */
void Peer::request(json data, Request* request){ 
    //find desired action in map of actions
    auto iter = requestMap.find( data["type"]);

    //call function
    if(iter != requestMap.end()){ 
        iter->second(this, data, request);
    }
    else{
        throw GlobalException("Exception raised: type of message not found");
    }
}

/**
 * @brief Thread function will send every 10s hello message to node
 * 
 * @param args  peer arguments
 * @param peer  peer objects
 */
void Peer::peerCommunicator(PeerArguments* args, Peer* peer){
    try
    {   
        json request = {
            {"type", "hello"},
            {"txid", peer->getStorage()->getTransactionNumber()},
            {"username", args->username},
            {"ipv4", args->chatIpv4},
            {"port", args->chatPort}
        };
        //i represents ammount of second that thread sleeps
        int i = 0;  
        do
        {
            if(i == 10)
                i = 0;
            //send hello every 10s
            if(i == 0){
                peer->sendSocket(request);
                request["txid"] = peer->getStorage()->getTransactionNumber();
            }
            //sleep for 1s
            std::this_thread::sleep_for(std::chrono::seconds(1));
            i++;
        //while hello is not stopped
        } while (!peer->getStorage()->getHello());
        
    }
    catch(const std::exception& e)
    {
        peer->getStorage()->setExc();
        std::cerr << e.what() << '\n';
    }
}
/**
 * @brief Method disconects peer from node with Hello message
 * 
 */
void Peer::disconnectFromNode(){
    //send disconnect message
    json request = {
            {"type", "hello"},
            {"txid", storage->getTransactionNumber()},
            {"username", peerArguments->username},
            {"ipv4", "0.0.0.0"},
            {"port", 0}
        };
    sendSocket(request);
}

/**
 * @brief Disconnects peer from existing node (disconnectFromNode()) and connects it to node
 * defined by parameters
 * 
 * @param ipv4 of node
 * @param port of node
 */
void Peer::reconect(std::string ipv4, unsigned short port){
    //stop thread
    getStorage()->setHello(true);
    peerConnectionThread.join();
    //disconnect 
    disconnectFromNode();
    //create connection structure
    this->requestAddr = Socket::createRequest(ipv4, port);
    //flip flag
    getStorage()->setHello(false);
    //start thread
    peerConnectionThread = std::thread(peerCommunicator, peerArguments, this);
}
/**
 * @brief Send data to connected node
 * 
 * @param data 
 */
void Peer::sendSocket(json data){
    socket->sendData(data, requestAddr);
}

/**
 * @brief Send data to node/peer defined in req structure
 * 
 * @param data 
 * @param req 
 */
void Peer::sendSocket(json data, Request* req){
    socket->sendData(data, req);
}

/**
 * @brief Send data to node/peer defined in req structure with best effort
 * 
 * @param data 
 * @param req 
 */
void Peer::sendSocketWait(json data, Request* req){
    int ackNumber = data["txid"];
    socket->sendData(data, req);
    
    //try to send message 2x more times
    for(int i = 0; i < 2; i++){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if(storage->acknowledge(ackNumber))
            return;
        socket->sendData(data, req);
    }
    throw LocalException("Exception raised: Send data timeout");
}

/**
 * @brief Run comm thread
 * 
 */
void Peer::runCommunicator(){
    peerConnectionThread = std::thread(peerCommunicator, peerArguments, this);
}
/**
 * @brief Send data to connected node with best effort
 * 
 * @param data 
 */
void Peer::sendSocketWait(json data){
    sendSocketWait(data, requestAddr);
}

/**
 * @brief Getter
 * 
 * @return PeerStorage* 
 */
PeerStorage* Peer::getStorage(){
    return this->storage;
}

/**
 * @brief Setter
 * 
 * @param socket 
 */
void Peer::setSocket(Socket* socket){
    this->socket = socket;
}