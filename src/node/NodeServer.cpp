#include "NodeServer.h"

NodeServer::NodeServer(Socket* socket)
{
    this->socket = socket;
    this->socket->bindSocket();
}

NodeServer::~NodeServer()
{
    this->socket->~Socket();
}

void worker(int id, NodeWork* work){    
    try
    {
        work->node->request(work->data, work->req);
    }

    catch(const GlobalException& e)
    {
            std::cerr << e.what() << '\n';
            json error = {
                {"type", "error"},
                {"txid", work->node->getStorage()->getTransactionNumber()},
                {"verbose", e.what()}
            };
            work->node->sendSocket(error, work->req);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}


void NodeServer::listen(Node* node, int threadPoolSize){
    try{
        ctpl::thread_pool p(threadPoolSize);
        do{
            Request* req = new Request();
            req->addrLen = sizeof(struct sockaddr_in);

            json recvData = socket->recvData(req);
            if(recvData["type"] != "update"){
                std::cout << "New data from: " << inet_ntoa(req->addr.sin_addr)<<" : "<< ntohs(req->addr.sin_port) << std::endl;
                std::cout << recvData.dump() << std::endl;
            }
            
            NodeWork* work = new NodeWork();
            work->node = node;
            work->req = req;
            work->data = recvData;

            
            p.push(worker, work);

        } while (!node->getStorage()->getIsExc());
    }
    catch(const std::exception& e)
    {
        node->getStorage()->setExc();
        std::cerr << e.what() << '\n';
    }         
}
