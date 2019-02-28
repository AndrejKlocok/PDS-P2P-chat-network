#include "NodePeerServer.h"

NodePeerServer::NodePeerServer(/* args */)
{
}

NodePeerServer::~NodePeerServer()
{
}

void  NodePeerServer::peerWorker(Node* node, Request* req, Socket* socket, json* data){
    std::cout << "Sent data" << std::endl;
    socket->sendData(*data, req);

}

void NodePeerServer::listen(Node* node){

    Request* req = new Request();
    req->addrLen = sizeof(struct sockaddr_in);
    try{
        //rpc loop while exception does not occur
        do{
            json recvData = socket->recvData(req);
            std::cout << "New data from: " << inet_ntoa(req->addr.sin_addr)<<" : "<< req->addr.sin_port << std::endl;
            std::cout << recvData.dump() << std::endl;
            //spawn thread
            //std::thread t1(NodePeerServer::peerWorker, node, req, socket, &recvData);
            //t1.join();

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