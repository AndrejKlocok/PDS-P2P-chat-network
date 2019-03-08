#include "NodeServer.h"

NodeServer::NodeServer(std::string IP, unsigned short port)
{
    this->socket = new Socket(IP, port);
    this->socket->bindSocket();
}

NodeServer::~NodeServer()
{
    //join threads
    for (size_t i = 0; i < threads.size(); i++) {
        if(threads.at(i).joinable()){
            threads.at(i).join();
        }
    }
    this->socket->~Socket();
}

void  NodeServer::peerWorker(Node* node, Request* req, Socket* socket, json data){    
   try
   {
       node->nodeRequest(data, req, socket); 
   }
   catch(const std::exception& e)
   {
       std::cerr << e.what() << '\n';
   }
}

void NodeServer::listen(Node* node){

    Request* req = new Request();
    req->addrLen = sizeof(struct sockaddr_in);
    try{
        //rpc loop while exception does not occur
        do{
            json recvData = socket->recvData(req);
            std::cout << "New data from: " << inet_ntoa(req->addr.sin_addr)<<" : "<< req->addr.sin_port << std::endl;
            std::cout << recvData.dump() << std::endl;
            
            //spawn thread
            threads.push_back(std::thread(peerWorker, node, req, socket, recvData));

        } while (!node->getIsExc());
    }
    catch(const std::exception& e)
    {
        node->setExc();
        std::cerr << e.what() << '\n';
    }         
}
