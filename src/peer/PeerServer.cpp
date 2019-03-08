#include "PeerServer.h"

PeerServer::PeerServer(std::string IP, unsigned short port)
{
    this->socket = new Socket(IP, port);
    this->socket->bindSocket();
}

PeerServer::~PeerServer()
{
        //join threads
    for (size_t i = 0; i < threads.size(); i++) {
        if(threads.at(i).joinable()){
            threads.at(i).join();
        }
    }
    this->socket->~Socket();
}

void  PeerServer::worker(Peer* peer, Request* req, Socket* socket, json data){
   try
   {
       peer->request(data, req, socket); 
   }
   //send back custom exception, f.e. ack not found
   catch(const CustomException& e)
   {
        std::cerr << e.what() << '\n';
        json error = {
            {"type", "error"},
            {"txid", peer->getTransactionNumber()},
            {"verbose", e.what()}
        };
        socket->sendData(error);
   }
   catch(const std::exception& e)
   {
       std::cerr << e.what() << '\n';
   }

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
            threads.push_back(std::thread(worker, peer, req, socket, recvData));
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
