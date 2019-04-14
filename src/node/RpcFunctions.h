#ifndef RPCFUNCTIONS_H
#define RPCFUNCTIONS_H

#include "Node.h"

class Node;

void onDatabase(Node* node, json* data);
void onNeighbors(Node* node, json* data);
void onConnect(Node* node, json* data);
void onDisconnect(Node* node, json* data);
void onSync(Node* node, json* data);
void onDump(Node* node, json* data);

#endif // !RPCFUNCTIONS_H