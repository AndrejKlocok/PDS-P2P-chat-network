#include "NodeRPCServer.h"

NodeRPCServer::NodeRPCServer(ushort port)
{
    socket = new Socket("", port);
    socket->setReusePort();
    socket->bindSocket();  
}

NodeRPCServer::~NodeRPCServer()
{
}

void NodeRPCServer::listen(Node* node){

    Request* req = new Request();
    req->addrLen = sizeof(struct sockaddr_in);
    try{
        //rpc loop
        do{
            json recvData = socket->recvData(req);
            std::cout << "New data from: " << inet_ntoa(req->addr.sin_addr)<<" : "<< req->addr.sin_port << std::endl;
            std::cout << recvData.dump() << std::endl;
            std::cout << "Sent data" << std::endl;
            socket->sendData(recvData, req); 
           
        } while (!node->getIsExc());
    }
    catch(const SocketDataExc& e){
        std::cerr << e.what() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    } 
}