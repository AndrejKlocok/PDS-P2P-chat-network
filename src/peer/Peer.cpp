#include "Peer.h"

Peer::Peer(PeerArguments* args, Socket* socket)
{
    this->isExc = false;
    this->isHello = false;
    this->peerArguments = args;
    this->transactionNumber = 0;
    this->socket = socket;
    this->requestAddr = Socket::createRequest(args->regIpv4, args->regPort);

    rpcMap["getlist"] = onGetList;
    rpcMap["message"] = onMessage;
    rpcMap["peers"] = onPeers;
    rpcMap["reconnect"] = onReconnect;

    requestMap["list"]  = onList;
    requestMap["error"] = onError;
    requestMap["ack"]   = onAck;
    requestMap["message"]   = onMessage;

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

void Peer::request(json data, Request* request){ 

    //find desired action in map of actions
    auto iter = requestMap.find( data["type"]);

    //call function
    if(iter != requestMap.end()){ 
        iter->second(this, data, request);
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
            //sleep for 1s
            std::this_thread::sleep_for(std::chrono::seconds(1));
            i++;

        } while (!peer->getHello());
        
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
    sendSocket(request);
}

void Peer::reconect(std::string ipv4, unsigned short port){
    setHello(true);
    peerConnectionThread.join();
    disconnectFromNode();
    
    this->requestAddr = Socket::createRequest(ipv4, port);
    
    setHello(false);
    peerConnectionThread = std::thread(peerCommunicator, peerArguments, this);
}

void Peer::insertMessage(json message){
    std::scoped_lock(msgMutex);
    this->messages.push_back(message);
}

void Peer::sendMessages(json peers){
   json msg = getFrontMessage();

    for(json peer : peers){
        if(msg["to"] == peer["username"]){
            std::cout<<"Sending message\n";
            msg["txid"] = getTransactionNumber();
            Request* consignee = Socket::createRequest(peer["ipv4"], peer["port"]);
            sendSocket(msg, consignee);
            waitAck(msg["txid"]);
            break;
        }
    }
}

json Peer::getFrontMessage(){
    json msg;

    if(messages.empty()){
        throw PeerMsgEmpty();
    }
    else{
        std::scoped_lock(msgMutex);
        msg = messages.front();
        messages.pop_front();
    }
    
    return msg;
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

void Peer::waitAck(int ackNumber){
    // wait for ack 
    std::this_thread::sleep_for(std::chrono::seconds(1));

     if(!acknowledge(ackNumber)){
        throw CustomException("Exception raised: ack %d not received", ackNumber);
    }
}

void Peer::setExc(){
    this->isExc = true;
    this->isHello = true;
}

bool Peer::getIsExc(){
    return this->isExc;
}

void Peer::sendSocket(json data){
    socket->sendData(data, requestAddr);
}
void Peer::sendSocket(json data, Request* req){
    socket->sendData(data, req);
}

bool Peer::getHello(){
    return this->isHello;
}

void Peer::setHello(bool value){
    this->isHello = value;
}

bool Peer::getPeerDist(){
    return this->peersDisp;
}

void Peer::setPeerDisp(bool value){
    this->peersDisp = value;
}