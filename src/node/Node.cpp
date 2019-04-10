#include "Node.h"

Node::Node(NodeArguments* args)
{
    this->storage = new NodeStorage(this);
    this->args = args;
    this->me = args->regIpv4+","+std::to_string(args->regPort);
}

Node::~Node(){
    disconnect();

    storage->emptyNeighbors();
    for( auto it = updateThreads.begin(); it != updateThreads.end(); ++it ) {
        if(it->second.joinable()){
            it->second.join();
        }
    }
    //notify peers
}

void Node::registerRpcRequest(std::string keyName, rpcFunction func){
    rpcMap[keyName] = func;
}

void Node::registerBaseRequest(std::string keyName, baseFunction func){
    requestMap[keyName] = func;
}

void Node::rpcRequest(json* request){
    //find desired action in map of actions
    auto iter = rpcMap.find( (*request)["type"]);

    //call function
    if(iter != rpcMap.end()){
        iter->second(this, request);
    }
    else{
        throw UnknownType();
    }
}

void Node::request(json data, Request* request){

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

NodeStorage* Node::getStorage(){
    return this->storage;
}


void Node::nodeUpdate(Node* node, std::pair<std::string, unsigned int> ip_port){
    try
    {   
        Request* request = Socket::createRequest(ip_port.first, ip_port.second);
        json update = {
            {"type", "update"}
        };
        //i represents ammount of second that thread sleeps
        int i = 0;  
        do
        {
            if(i == 4)
                i = 0;
            //send update every 4s
            if(i == 0){
                update["txid"] = node->getStorage()->getTransactionNumber();
                update["db"] = node->getStorage()->getDbRecords();
                node->sendSocket(update, request);
            }
            //sleep for 1s
            std::this_thread::sleep_for(std::chrono::seconds(1));
            i++;

        } while (node->getStorage()->incNodeTimer(ip_port, 1) && !node->getStorage()->getIsExc()); 
        
        std::cout<<"Timeout\n";
        
        //if node is disconnecting do nothing else notify that node is disconnected
        if(!node->getStorage()->getIsDisc())
            node->getStorage()->addDiscNeighbor(ip_port);
    }
    catch(const std::exception& e)
    {
        //node->getStorage()->setExc();
        std::cerr << e.what() << '\n';
    }
}

void Node::releaseThread(std::pair<std::string, unsigned int> ip_port){
    auto iter = updateThreads.find(ip_port);

    if(iter != updateThreads.end()){ 
        //timeout
        if(iter->second.joinable()){
            iter->second.join();
            std::scoped_lock(updateThreadMutex);
            updateThreads.erase(iter);
            return;
        }
        //thread is working, NodeRecord created, but did not existed in connectNode method, thus
        //thread should have stopped already, so this case should not exists
        
        throw CustomException("Exception raised: Thread realease curruption for%s,%d", ip_port.first.c_str(), ip_port.second);
    }
}

bool Node::connectNode(std::string ipv4, unsigned int port, bool authority){
    auto ip_port = std::make_pair(ipv4, port);
    
    //cant connect to myself
    if(this->args->regIpv4 == ipv4 && this->args->regPort == port){
        return false;
    }

    if(!storage->getIsDisc() && storage->addNeighbor(ipv4, port, authority)){
        //check if it is not timeouted connection
        releaseThread(ip_port);
        updateThreads[ip_port] = std::thread(nodeUpdate, this, ip_port);

        return true;
    }
    else{
        return false;
    }
}

void Node::disconnect(){
    json disconnect = {
        {"type", "disconnect"}
    };
    storage->setDisc(true);
    for(auto neighbor : storage->getNeighbors())
    {  
        disconnect["txid"] = storage->getTransactionNumber(); 
        storage->deleteNeighbor(neighbor.first.first, neighbor.first.second);
        sendSocket(disconnect, neighbor.second->request);
    }
}

void Node::sendSocket(json data, Request* req){
    socket->sendData(data, req);
}

void Node::sendSocketWait(json data, Request* req){
    int ackNumber = data["txid"];
    socket->sendData(data, req);
    
    //try to send message 2x more times
    for(int i = 0; i < 2; i++){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if(storage->acknowledge(ackNumber))
            break;
        socket->sendData(data, req);
    }   
}

void Node::setSocket(Socket* socket){
    this->socket = socket;
}

NodeArguments* Node::getArguments(){
    return args;
}

std::string Node::getMe(){
    return me;
}