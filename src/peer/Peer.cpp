#include "Peer.h"

Peer::Peer(PeerArguments* args, Socket* socket)
{
    this->isExc = false;
    this->peerArguments = args;
    this->transactionNumber = 0;
    this->socket = socket;
    this->requestAddr = socket->createRequest(args->regIpv4, args->regPort);

    rpcMap["onGetList"] = onGetList;
    rpcMap["onMessage"] = onMessage;
    rpcMap["onPeers"] = onPeers;
    rpcMap["onReconnect"] = onReconnect;

    requestMap["list"]        = onList;
    requestMap["error"]       = onError;

    peerConnectionThread = std::thread(peerCommunicator, args, this);
}

Peer::~Peer(){
    this->setExc();
    peerConnectionThread.join();
    disconnectFromNode();
    this->socket->~Socket();
}


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

void Peer::request(json data, Request* request, Socket* socket){

    //find desired action in map of actions
    auto iter = requestMap.find( data["type"]);

    //call function
    if(iter != requestMap.end()){ 
        iter->second(this, data, request, socket);
    }
    else{
        throw UnknownType();
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
            {"txid", peer->getTransactionNumber()},
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
                request["txid"] = peer->getTransactionNumber();
            }
            //sleep for 10s
            std::this_thread::sleep_for(std::chrono::seconds(1));
            i++;

        } while (!peer->getIsExc());
        
    }
    catch(const std::exception& e)
    {
        peer->setExc();
        std::cerr << e.what() << '\n';
    }
}

void Peer::disconnectFromNode(){
    //send disconnect message
    json request = {
            {"type", "hello"},
            {"txid", getTransactionNumber()},
            {"username", peerArguments->username},
            {"ipv4", 0},
            {"port", 0}
        };
    
    socket->sendData(request);

    // free socket
    socket->~Socket();
}

unsigned short Peer::getTransactionNumber(){
    transactionNumber++;
    return transactionNumber;
}

bool Peer::acknowledge(unsigned short txid){
    auto iter = find (acknowledgements.begin(), acknowledgements.end(), txid);
    
    //acknowledgement was not found
    if(iter == acknowledgements.end())
        return false;

    std::scoped_lock(ackMutex);
    acknowledgements.erase(iter);
    return true;
}

void Peer::insertAck(unsigned short txid){
    std::scoped_lock(ackMutex);
    acknowledgements.push_back(txid);
}

void Peer::setExc(){
    this->isExc = true;
}

bool Peer::getIsExc(){
    return this->isExc;
}

void Peer::sendSocket(json data){
    socket->sendData(data, requestAddr);
}
