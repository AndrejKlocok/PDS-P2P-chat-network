#include "NodeHandle.h"

NodeHandle::NodeHandle(/* args */){}

NodeHandle::~NodeHandle(){}

void NodeHandle::processRequest(int argc){
    if(argc != 7 ){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    std::cout<<"IP: " << args.regIpv4<<", Port: "<<args.regPort<<std::endl; 
    
    try
    {

        Node* node = new Node(this->args.id);
        std::thread rpcThread(rpcServer, node);
        std::thread peerThread(peerServer, node);
        std::thread nodeThread(nodeServer, node);

        rpcThread.join();
        peerThread.join();
        nodeThread.join();

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void NodeHandle::rpcServer(Node* node){
    try
    {
        NodeRPCServer* rpcServer  = new NodeRPCServer(6969);
        rpcServer->listen(node);
    }
    catch(const std::exception& e)
    {
        node->setExc();
        std::cerr << e.what() << '\n';
    }
    
}

void NodeHandle::peerServer(Node* node){

}

void NodeHandle::nodeServer(Node* node){

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