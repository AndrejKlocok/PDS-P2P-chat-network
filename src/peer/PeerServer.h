#ifndef PEERSERVER_H
#define PEERSERVER_H

#include <thread>

#include "common/Socket.h"
#include "Peer.h"
#include "../libs/ctpl_stl.h"

struct PeerWork
{
    Peer* peer;
    Request* req;
    json data;
};


class PeerServer
{
private:
    Socket* socket;
public:
    PeerServer(Socket* socket);
    ~PeerServer();
    void listen(Peer* peer, int threadPoolSize);
};

#endif // !PEERSERVER_H