#include "PeerServer.h"

PeerServer::PeerServer(Socket* socket)
{
    this->socket = socket;
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
    //this->socket->~Socket();
}

void  PeerServer::worker(Peer* peer, Request* req, json data){
   try
   {
       peer->request(data, req); 
   }
   //send back custom exception, f.e. ack not found
   catch(const GlobalException& e)
   {
        std::cerr << e.what() << '\n';
        json error = {
            {"type", "error"},
            {"txid", peer->getStorage()->getTransactionNumber()},
            {"verbose", e.what()}
        };
        peer->sendSocket(error, req);
   }
   catch(const PeerMsgEmpty& e){}
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
            std::cout << "New data from: " << inet_ntoa(req->addr.sin_addr)<<" : "<< ntohs(req->addr.sin_port) << std::endl;
            std::cout << recvData.dump() << std::endl;
            //spawn thread
            threads.push_back(std::thread(worker, peer, req, recvData));

        } while (!peer->getStorage()->getIsExc());
    }
    catch(const SocketDataExc& e){
        std::cerr << e.what() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    } 
}
