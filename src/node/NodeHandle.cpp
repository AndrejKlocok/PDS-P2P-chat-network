#include "NodeHandle.h"

NodeHandle::NodeHandle(/* args */){}

NodeHandle::~NodeHandle(){
    unlink(this->pipeName.c_str());
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
        this->pipeName = std::to_string(args.id);

        Node* node = new Node();
        
        //spawn rpc worker
        std::thread rpcThread(rpcServer, node, this->pipeName);
        
        //create server and listen
        server = new NodeServer(this->args.regIpv4, this->args.regPort);
        server->listen(node); 

        //wait for rpc thread to finish
        rpcThread.join();
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void NodeHandle::rpcServer(Node* node, std::string pipeName){
    int fd;             //descriptor
    char c;             //char 
    std::string buff;   //buffer
    json request;       //request to node
    json response;      //response from node
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
                std::cout<< request.dump()<<std::endl;
                node->rpcRequest(&request, &response);

            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }

            buff.clear();
            
        } while (!node->getIsExc());
        
    }
    catch(const std::exception& e)
    {
        node->setExc();
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