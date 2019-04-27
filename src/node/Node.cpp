#include "Node.h"
/**
 * @brief Construct a new Node:: Node object
 * 
 * @param args 
 */
Node::Node(NodeArguments* args)
{
    this->storage = new NodeStorage(this);
    this->args = args;
    this->me = args->regIpv4+","+std::to_string(args->regPort);
    this->updateThread = std::thread(nodeUpdate, this);
}

/**
 * @brief Destroy the Node:: Node object
 * 
 */
Node::~Node(){
    try
    {
        storage->emptyNeighbors();
        if(updateThread.joinable()){
            updateThread.join();
        }
        //notify peers
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
/**
 * @brief Register new RPC request (rpc function)
 * 
 * @param keyName
 * @param func 
 */
void Node::registerRpcRequest(std::string keyName, rpcFunction func){
    rpcMap[keyName] = func;
}

/**
 * @brief Register new Base request (node function) for server
 * 
 * @param keyName 
 * @param func 
 */
void Node::registerBaseRequest(std::string keyName, baseFunction func){
    requestMap[keyName] = func;
}

/**
 * @brief Handle rpc request according to map of rpc functions
 * 
 * @param request 
 */
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

/**
 * @brief Handle base request according to map of node functions
 * 
 * @param data 
 * @param request 
 */
void Node::request(json data, Request* request){

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
 * @brief Node`s opdate thread function, that sends evert 4s update msg to specified node
 * 
 * @param node object
 * @param ip_port pair
 */
void Node::nodeUpdate(Node* node){
    try
    {   
        json update = {
            {"type", "update"}
        };
        //i represents ammount of second that thread sleeps
        NodeStorage* storage = node->getStorage();
        int i = 0;  
        do
        {
            if(i == 4)
                i = 0;
            //send update every 4s
            if(i == 0){
                update["db"] = storage->getDbRecords();
                //foreach neighbor send update
                for(auto neighbor : storage->getNeighbors())
                {
                    update["txid"] = storage->getTransactionNumber();
                    node->sendSocket(update, neighbor.second->request);
                }
            }
            for(auto neighbor : storage->getNeighbors())
            {
                if(!storage->incNodeTimer(neighbor.first, 1) && !storage->getIsDisc() ){
                    storage->addDiscNeighbor(neighbor.first);
                }
            }
            //sleep for 1s
            std::this_thread::sleep_for(std::chrono::seconds(1));
            i++;

        } while (!node->getStorage()->getIsExc()); 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief Node`s disconnect thread function, that sends disconnect message to neighbor
 * 
 * @param node object
 * @param ip_port pair
 * @param request structure
 */
void Node::nodeDisconnect(Node* node, std::pair<std::string, unsigned int> ip_port, Request* request){
    json disconnect = {
        {"type", "disconnect"}
    };
    NodeStorage* storage = node->getStorage();
    disconnect["txid"] = storage->getTransactionNumber(); 
    storage->deleteNeighbor(ip_port.first, ip_port.second);
    node->sendSocketWait(disconnect, request);
}

/**
 * @brief Method tries to make a new neighbor with node, according to given parameters
 * 
 * @param ipv4 string
 * @param port number
 * @param authority 
 * @return true neighbor created
 * @return false already connected
 */
bool Node::connectNode(std::string ipv4, unsigned int port, bool authority){
    auto ip_port = std::make_pair(ipv4, port);
    
    //cant connect to myself
    if(this->args->regIpv4 == ipv4 && this->args->regPort == port){
        return false;
    }

    if(!storage->getIsDisc() && storage->addNeighbor(ipv4, port, authority)){
        return true;
    }
    else{
        return false;
    }
}

/**
 * @brief Disconnect node from other neighbors
 * 
 */
void Node::disconnect(){
    storage->setDisc(true);

    std::vector<std::thread> threads_disconnect;

    //spawn disconnect threads
    for(auto neighbor : storage->getNeighbors())
    {  
        std::thread th (nodeDisconnect, this, neighbor.first, neighbor.second->request);
        threads_disconnect.push_back(std::move(th));
    }

    //join them
    for(std::thread &th : threads_disconnect)
    {
        th.join();
    }
}

/**
 * @brief Send data with stored socket
 * 
 * @param data json
 * @param req structure
 */
void Node::sendSocket(json data, Request* req){
    socket->sendData(data, req);
}

/**
 * @brief Send data with stored socket with maximum effort (3x)
 * 
 * @param data 
 * @param req 
 */
void Node::sendSocketWait(json data, Request* req){
    int ackNumber = data["txid"];
    socket->sendData(data, req);
    
    //try to send message 2x more times
    for(int i = 0; i < 2; i++){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if(storage->acknowledge(ackNumber))
            return;
        socket->sendData(data, req);
    } 
    throw GlobalException("Exception raised: Send data timeout");
}

/**
 * @brief Return node storage object
 * 
 * @return NodeStorage* 
 */
NodeStorage* Node::getStorage(){
    return this->storage;
}

/**
 * @brief Return socket object
 * 
 * @param socket 
 */
void Node::setSocket(Socket* socket){
    this->socket = socket;
}

/**
 * @brief Return arguments
 * 
 * @return NodeArguments* 
 */
NodeArguments* Node::getArguments(){
    return args;
}

/**
 * @brief Return node identification
 * 
 * @return std::string 
 */
std::string Node::getMe(){
    return me;
}