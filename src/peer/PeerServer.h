#ifndef PEERSERVER_H
#define PEERSERVER_H

#include <thread>

#include "common/Socket.h"
#include "Peer.h"

class PeerServer
{
private:
    Socket* socket;
public:
    PeerServer(std::string IP, unsigned short port);
    ~PeerServer();
    void listen(Peer* peer);
    void static peerWorker(Peer* peer, Request* req, Socket* socket, json* data);
};

#endif // !PEERSERVER_H