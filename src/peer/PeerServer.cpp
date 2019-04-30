/**
 * @file PeerServer.cpp
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
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

/**
 * @brief Worker thread function
 * 
 * @param id of thread
 * @param work description of work
 */
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

/**
 * @brief Listens on port, accepts UDP requests and pushes them to the pool.
 * 
 * @param node object
 * @param threadPoolSize size of threadpool
 */
void PeerServer::listen(Peer* peer, int threadPoolSize){
    try{
        ctpl::thread_pool p(threadPoolSize);
        do{
            Request* req = new Request();
            req->addrLen = sizeof(struct sockaddr_in);          
            
            try
            {
                json recvData = socket->recvData(req);
            
                PeerWork* work = new PeerWork();
                work->peer = peer;
                work->req = req;
                work->data = recvData;

                p.push(worker, work);
            }
            catch(const BencodeExc& e){
                std::cerr << e.what() << '\n';
                json error = {
                    {"type", "error"},
                    {"txid", peer->getStorage()->getTransactionNumber()},
                    {"verbose", e.what()}
                };
                peer->sendSocket(error, req);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        } while (!peer->getStorage()->getIsExc());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        peer->getStorage()->setExc();
    } 
}
