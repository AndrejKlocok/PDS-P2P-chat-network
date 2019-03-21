#include "NodeServer.h"

NodeServer::NodeServer(Socket* socket)
{
    this->socket = socket;
    this->socket->bindSocket();
}

NodeServer::~NodeServer()
{
    //disc nodes/peers maybe
    //join threads
    for (size_t i = 0; i < threads.size(); i++) {
        if(threads.at(i).joinable()){
            threads.at(i).join();
        }
    }
    this->socket->~Socket();
}

void  NodeServer::worker(Node* node, Request* req, json data){    
   try
   {
       node->request(data, req);
   }
   //send back custom exception, f.e. ack not found
   catch(const CustomException& e)
   {
        std::cerr << e.what() << '\n';
        json error = {
            {"type", "error"},
            {"txid", node->getStorage()->getTransactionNumber()},
            {"verbose", e.what()}
        };
        node->sendSocket(error, req);
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
            std::cout << "New data from: " << inet_ntoa(req->addr.sin_addr)<<" : "<< ntohs(req->addr.sin_port) << std::endl;
            std::cout << recvData.dump() << std::endl;
            
            //spawn thread
            threads.push_back(std::thread(worker, node, req, recvData));

        } while (!node->getStorage()->getIsExc());
    }
    catch(const std::exception& e)
    {
        node->getStorage()->setExc();
        std::cerr << e.what() << '\n';
    }         
}
