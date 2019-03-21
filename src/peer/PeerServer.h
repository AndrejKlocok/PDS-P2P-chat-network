#ifndef PEERSERVER_H
#define PEERSERVER_H

#include <thread>

#include "common/Socket.h"
#include "Peer.h"

class PeerServer
{
private:
    Socket* socket;
    std::vector<std::thread> threads;
public:
    PeerServer(Socket* socket);
    ~PeerServer();
    void listen(Peer* peer);
    void static worker(Peer* peer, Request* req, json data);
};

#endif // !PEERSERVER_H