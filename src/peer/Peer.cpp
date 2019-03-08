#include "Peer.h"

Peer::Peer(PeerArguments* args)
{
    this->isExc = false;
    this->peerArguments = args;
    this->transactionNumber = 0;
    peerFunctions["onGetList"] = onGetList;
    peerFunctions["onMessage"] = onMessage;
    peerFunctions["onPeers"] = onPeers;
    peerFunctions["onReconnect"] = onReconnect;

    socket = new Socket(args->regIpv4, args->regPort);

    peerConnectionThread = std::thread(peerCommunicator, args, this);
}

Peer::~Peer(){
    this->setExc();
    peerConnectionThread.join();
    disconnectFromNode();
    this->socket->~Socket();
}


void Peer::peerRequest(json request){

    //find desired action in map of actions
    auto iter = peerFunctions.find(request["type"]);

    //call function
    if(iter != peerFunctions.end()){
        iter->second(this, &request);
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
            if(i == 0)
                peer->getSocket()->sendData(request);
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

void Peer::setExc(){
    this->isExc = true;
}

bool Peer::getIsExc(){
    return this->isExc;
}

Socket* Peer::getSocket(){
    return socket;
}

int Peer::getTransactionNumber(){
    return transactionNumber++;
}