#include "NodeServer.h"

NodeServer::NodeServer(Socket* socket)
{
    this->socket = socket;
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

void  NodeServer::worker(Node* node, Request* req, json data){    
    try
    {
        node->request(data, req);
    }

    catch(const GlobalException& e)
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
    try{
        do{
            Request* req = new Request();
            req->addrLen = sizeof(struct sockaddr_in);

            json recvData = socket->recvData(req);
            std::cout << "New data from: " << inet_ntoa(req->addr.sin_addr)<<" : "<< ntohs(req->addr.sin_port) << std::endl;
            std::cout << recvData.dump() << std::endl;
            
            //spawn thread
            threads.push_back(std::thread(worker, node, req, recvData));
            /*
            if(threads.size() > 10){
                std::cout << "Joining threads start" << '\n';
                for(auto it = threads.begin(); it != threads.end(); it++)    {
                    //join and erase
                    if(it->joinable()){
                        it->join();
                        threads.erase(it);
                    }
                }
                std::cout << "Joined to " << threads.size() << '\n';
            }*/

        } while (!node->getStorage()->getIsExc());
    }
    catch(const std::exception& e)
    {
        node->getStorage()->setExc();
        std::cerr << e.what() << '\n';
    }         
}
