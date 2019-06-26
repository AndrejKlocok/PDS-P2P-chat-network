/**
 * @file NodeServer.cpp
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
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

/**
 * @brief Worker thread function
 * 
 * @param id of thread
 * @param work description of work
 */
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

/**
 * @brief Listens on port, accepts UDP requests and pushes them to the pool.
 * 
 * @param node object
 * @param threadPoolSize size of threadpool
 */
void NodeServer::listen(Node* node, int threadPoolSize){
    try{
        ctpl::thread_pool p(threadPoolSize);
        do{
            Request* req = new Request();
            req->addrLen = sizeof(struct sockaddr_in);
            // accept request
            try{
                json recvData = socket->recvData(req);
                // init work for thread
                NodeWork* work = new NodeWork();
                work->node = node;
                work->req = req;
                work->data = recvData;

                // push new work to the pool
                p.push(worker, work);
            }
            catch(const BencodeExc& e){
                std::cerr << e.what() << '\n';
                json error = {
                    {"type", "error"},
                    {"txid", node->getStorage()->getTransactionNumber()},
                    {"verbose", e.what()}
                };
                node->sendSocket(error, req);
            }
            catch (const std::exception& e){
                std::cerr << e.what() << '\n';
            }

        } while (!node->getStorage()->getIsExc());
    }
    catch(const std::exception& e)
    {
        node->getStorage()->setExc();
        std::cerr << e.what() << '\n';
    }         
}
