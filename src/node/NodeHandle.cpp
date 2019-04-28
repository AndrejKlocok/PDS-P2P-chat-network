#include "NodeHandle.h"

/**
 * @brief Construct a new Node Handle:: Node Handle object
 * 
 */
NodeHandle::NodeHandle(/* args */){}

/**
 * @brief Destroy the Node Handle:: Node Handle object
 * 
 */
NodeHandle::~NodeHandle(){
    unlink(this->pipeName.c_str());
    node->disconnect();
    node->getStorage()->setExc();

    node->~Node();
    server->~NodeServer();
}

/**
 * @brief Initialize node object 
 * 
 * @param argc 
 */
void NodeHandle::initNode(int argc){
    if(argc != 7 ){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    try
    {
        int threadsNumb = 0;
        std::map<std::string, std::string> config = readConfig("config");
        
        auto iter = config.find("ThreadPoolServer");

        if(iter != config.end()){
            threadsNumb = stoi(iter->second);
        }
        else{
            throw LocalException("Threadpool size not configured from config file");
        }
        
        node = new Node(&args);

        //register RPC functions
        node->registerRpcRequest("database", onDatabase);
        node->registerRpcRequest("neighbors", onNeighbors);
        node->registerRpcRequest("connect", onConnect);
        node->registerRpcRequest("disconnect", onDisconnect);
        node->registerRpcRequest("sync", onSync);

        //register base functions
        node->registerBaseRequest("hello", onHello);
        node->registerBaseRequest("getlist", onGetList);
        node->registerBaseRequest("error", onError);
        node->registerBaseRequest("ack", onAck);
        node->registerBaseRequest("update", onUpdate);
        node->registerBaseRequest("disconnect", onDisconnect);

        //set up socket connection
        Socket* socket = new Socket(args.regIpv4, args.regPort);
        node->setSocket(socket);
        //pipename
        this->pipeName = std::to_string(args.id);
        //node server
        server = new NodeServer(socket);

        std::thread nodeThread(nodeServer, node, server, threadsNumb);
        rpcServer(node, this->pipeName);
        nodeThread.join();
        
    }
    catch(const std::exception& e)
    {
        node->getStorage()->setExc();
        std::cerr << e.what() << '\n';
    }
}
/**
 * @brief RPC thread worker function 
 * 
 * @param node 
 * @param pipeName 
 */
void NodeHandle::rpcServer(Node* node, std::string pipeName){
    int fd;             //descriptor
    char c;             //char 
    std::string buff;   //buffer
    json request;       //request to node
    try
    {
        mkfifo(pipeName.c_str(), 0666);
        do
        {
           fd = open(pipeName.c_str(), O_RDONLY);
            
            //read
            while ( read(fd, &c, sizeof(c)) > 0 ){
                buff += c;
            }
            close(fd);
            try
            {
                request = json::parse(buff);
                node->rpcRequest(&request);

            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }

            buff.clear();
            
        } while (!node->getStorage()->getIsExc());
        
    }
    catch(const std::exception& e)
    {
        node->getStorage()->setExc();
        std::cerr << e.what() << '\n';
    }
    
}
/**
 * @brief Node server thread worker
 * 
 * @param node 
 * @param server 
 */
void NodeHandle::nodeServer(Node* node, NodeServer* server, int threadsNumb){
    //bind socket
    server->listen(node, threadsNumb); 
}

/**
 * @brief Setter
 * 
 * @param regPort 
 */
void NodeHandle::setRegPort(  unsigned short regPort){
    this->args.regPort = regPort;
}

/**
 * @brief Setter
 * 
 * @param regIpv4 
 */
void NodeHandle::setRegIpv4( std::string regIpv4){
    this->args.regIpv4 = regIpv4;
}

/**
 * @brief Setter
 * 
 * @param id 
 */
void NodeHandle::setId( unsigned short id){
    this->args.id = id;
}