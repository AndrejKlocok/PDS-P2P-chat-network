/**
 * @file PeerFunctions.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#ifndef PEERFUNCTIONS_H
#define PEERFUNCTIONS_H

#include "Peer.h"

class Peer;

void onList(Peer* peer, json data, Request* request);
void onAck(Peer* peer, json data, Request* request);
void onError(Peer* peer, json data, Request* request);
void onList(Peer* peer, json data, Request* request);
void onMessage(Peer* peer, json data, Request* request);
#endif // !PEERFUNCTIONS_H