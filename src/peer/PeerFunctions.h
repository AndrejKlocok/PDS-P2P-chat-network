#ifndef PEERFUNCTIONS_H
#define PEERFUNCTIONS_H

#include "Peer.h"

class Peer;

void onList(Peer* peer, json data, Request* request, Socket* socket);
void onAck(Peer* peer, json data, Request* request, Socket* socket);
void onError(Peer* peer, json data, Request* request, Socket* socket);

#endif // !PEERFUNCTIONS_H