#ifndef RPCFUNCTIONS_H
#define RPCFUNCTIONS_H

#include "Peer.h"

class Peer;

void onGetList(Peer* peer, json* json);
void onPeers(Peer* peer, json* json);
void onMessage(Peer* peer, json* json);
void onReconnect(Peer* peer, json* json);

#endif // !RPCFUNCTIONS_H