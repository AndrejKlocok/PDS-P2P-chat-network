#include "NodeHandle.h"

NodeHandle::NodeHandle(/* args */){}

NodeHandle::~NodeHandle(){
    unlink(this->pipeName.c_str());
    node->getStorage()->setExc();
    node->~Node();
    server->~NodeServer();
}

void NodeHandle::processRequest(int argc){
    if(argc != 7 ){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    std::cout<<"IP: " << args.regIpv4<<", Port: "<<args.regPort<<std::endl; 

    try
    {
        node = new Node(&args);

        node->registerRpcRequest("database", onDatabase);
        node->registerRpcRequest("neighbors", onNeighbors);
        node->registerRpcRequest("connect", onConnect);
        node->registerRpcRequest("disconnect", onDisconnect);
        node->registerRpcRequest("sync", onSync);

        node->registerBaseRequest("hello", onHello);
        node->registerBaseRequest("getlist", onGetList);
        node->registerBaseRequest("error", onError);
        node->registerBaseRequest("ack", onAck);
        node->registerBaseRequest("update", onUpdate);
        node->registerBaseRequest("disconnect", onDisconnect);

        Socket* socket = new Socket(args.regIpv4, args.regPort);
        node->setSocket(socket);
        this->pipeName = std::to_string(args.id);
        server = new NodeServer(socket);
        
        std::thread rpcThread(rpcServer, node, this->pipeName);
        
        server->listen(node); 

        rpcThread.join();
        
    }
    catch(const std::exception& e)
    {
        node->getStorage()->setExc();
        std::cerr << e.what() << '\n';
    }
}

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
                std::cout<< "RPC: "<< request.dump()<<std::endl;
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

void NodeHandle::setRegPort(  unsigned short regPort){
    this->args.regPort = regPort;
}

void NodeHandle::setRegIpv4( std::string regIpv4){
    this->args.regIpv4 = regIpv4;
}

void NodeHandle::setId( unsigned short id){
    this->args.id = id;
}