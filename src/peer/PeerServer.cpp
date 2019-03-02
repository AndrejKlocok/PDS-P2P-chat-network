#include "PeerServer.h"

PeerServer::PeerServer(std::string IP, unsigned short port)
{
    this->socket = new Socket(IP, port);
    this->socket->bindSocket();
}

PeerServer::~PeerServer()
{
}

void  PeerServer::peerWorker(Peer* peer, Request* req, Socket* socket, json* data){
    std::cout << "Sent data" << std::endl;
    socket->sendData(*data, req);

}

void PeerServer::listen(Peer* peer){

    Request* req = new Request();
    req->addrLen = sizeof(struct sockaddr_in);
    try{
        //rpc loop while exception does not occur
        do{
            json recvData = socket->recvData(req);
            std::cout << "New data from: " << inet_ntoa(req->addr.sin_addr)<<" : "<< req->addr.sin_port << std::endl;
            std::cout << recvData.dump() << std::endl;
            //spawn thread
            //std::thread t1(PeerServer::peerWorker, peer, req, socket, &recvData);
            //t1.join();

        } while (!peer->getIsExc());
    }
    catch(const SocketDataExc& e){
        std::cerr << e.what() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    } 
}
