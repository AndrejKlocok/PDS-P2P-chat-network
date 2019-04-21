#include "PeerServer.h"

PeerServer::PeerServer(Socket* socket)
{
    this->socket = socket;
    this->socket->bindSocket();
}

PeerServer::~PeerServer()
{
    this->socket->~Socket();
}

void  worker(int id, PeerWork* work){
   try
   {
       work->peer->request(work->data, work->req); 
   }
   //send back custom exception, f.e. ack not found
   catch(const GlobalException& e)
   {
        std::cerr << e.what() << '\n';
        json error = {
            {"type", "error"},
            {"txid", work->peer->getStorage()->getTransactionNumber()},
            {"verbose", e.what()}
        };
        work->peer->sendSocket(error, work->req);
   }
   catch(const PeerMsgEmpty& e){}
   catch(const std::exception& e)
   {
       std::cerr << e.what() << '\n';
   }

}

void PeerServer::listen(Peer* peer, int threadPoolSize){

    
    try{
        ctpl::thread_pool p(threadPoolSize);
        do{
            Request* req = new Request();
            req->addrLen = sizeof(struct sockaddr_in);          
            json recvData = socket->recvData(req);
            std::cout << "New data from: " << inet_ntoa(req->addr.sin_addr)<<" : "<< ntohs(req->addr.sin_port) << std::endl;
            std::cout << recvData.dump() << std::endl;
            
            PeerWork* work = new PeerWork();
            work->peer = peer;
            work->req = req;
            work->data = recvData;

            p.push(worker, work);

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
